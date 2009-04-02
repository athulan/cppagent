/*
* Copyright (c) 2008, AMT – The Association For Manufacturing Technology (“AMT”)
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the AMT nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* DISCLAIMER OF WARRANTY. ALL MTCONNECT MATERIALS AND SPECIFICATIONS PROVIDED
* BY AMT, MTCONNECT OR ANY PARTICIPANT TO YOU OR ANY PARTY ARE PROVIDED "AS IS"
* AND WITHOUT ANY WARRANTY OF ANY KIND. AMT, MTCONNECT, AND EACH OF THEIR
* RESPECTIVE MEMBERS, OFFICERS, DIRECTORS, AFFILIATES, SPONSORS, AND AGENTS
* (COLLECTIVELY, THE "AMT PARTIES") AND PARTICIPANTS MAKE NO REPRESENTATION OR
* WARRANTY OF ANY KIND WHATSOEVER RELATING TO THESE MATERIALS, INCLUDING, WITHOUT
* LIMITATION, ANY EXPRESS OR IMPLIED WARRANTY OF NONINFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. 

* LIMITATION OF LIABILITY. IN NO EVENT SHALL AMT, MTCONNECT, ANY OTHER AMT
* PARTY, OR ANY PARTICIPANT BE LIABLE FOR THE COST OF PROCURING SUBSTITUTE GOODS
* OR SERVICES, LOST PROFITS, LOSS OF USE, LOSS OF DATA OR ANY INCIDENTAL,
* CONSEQUENTIAL, INDIRECT, SPECIAL OR PUNITIVE DAMAGES OR OTHER DIRECT DAMAGES,
* WHETHER UNDER CONTRACT, TORT, WARRANTY OR OTHERWISE, ARISING IN ANY WAY OUT OF
* THIS AGREEMENT, USE OR INABILITY TO USE MTCONNECT MATERIALS, WHETHER OR NOT
* SUCH PARTY HAD ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.
*/

#include "agent.hpp"

/* Agent public methods */
Agent::Agent(
    std::string server,
    unsigned int port,
    std::string configXmlPath,
    unsigned int numAdapters
  )
{
  // Load the configuration for the Agent
  mConfig = new XmlParser(configXmlPath);
  
  mDevices = mConfig->getDevices();
  mDataItems = mConfig->getDataItems();
  
  mAdapterId = getCurrentTimeInSec();
  
  for (unsigned int i=0; i<numAdapters; i++)
  {
    Adapter * adapter = new Adapter(mAdapterId, server, port);
    adapter->setAgent(this);
    mAdapters.push_back(adapter);
  }
  
  // Sequence number and sliding buffer for data
  mSequence = 1;
  mSlidingBuffer = new sliding_buffer_kernel_1<ComponentEvent *>();
  mSlidingBuffer->set_size(SLIDING_BUFFER_EXP);
  
  // Mutex used for synchronized access to sliding buffer and sequence number
  mSequenceLock = new dlib::mutex;
}

Agent::~Agent()
{
  delete mSlidingBuffer;
  delete mSequenceLock;
  delete mConfig;
}

bool Agent::on_request(
    const std::string& path,
    std::string& result,
    const map_type& queries,
    const map_type& cookies,
    queue_type& new_cookies,
    const map_type& incoming_headers,
    map_type& response_headers,
    const std::string& foreign_ip,
    const std::string& local_ip,
    unsigned short foreign_port,
    unsigned short local_port,
    std::ostream& out
  )
{
  try 
  {
    // Parse the URL path
    std::string::size_type loc1 = path.find("/", 1);
    
    std::string::size_type end;
    end = (path[path.length()-1] == '/') ? path.length()-1 : std::string::npos;
    
    if (loc1 < end) // If a '/' was found
    {
      std::string::size_type loc2 = path.find("/", loc1+1);
      
      if (loc2 == end)
      {
        return handleCall(
            out,
            result,
            queries,
            path.substr(loc1+1, loc2-loc1-1),
            path.substr(1, loc1-1)
          );
      }
      else
      {
        result = printError(
            "ROUTING_ERROR",
            "The path '" + path + "' does not exist."
          );
        return true;
      }
    }
    else
    {
      return handleCall(out, result, queries, path.substr(1, loc1-1));
    }
  }
  catch (std::exception & e)
  {
    std::cerr << "Agent.cpp Server Exception: " << e.what() << std::endl;
  }
  
  return true;
}

void Agent::addToBuffer(std::string time, std::string key, std::string value)
{
  DataItem * d = getDataItemByName(key);
  
  if (d == NULL)
  {
    std::cerr << "Agent.cpp: Could not find data item " << key << std::endl;
  }
  else
  { 
    mSequenceLock->lock();
    
    ComponentEvent * event = new ComponentEvent(d, mSequence, time, value);
    (*mSlidingBuffer)[mSequence] = event;
    d->setLatestEvent(event);
    
    mSequence++;
    mSequenceLock->unlock();
  }
}

/* Agent protected methods */
std::string Agent::devicesAndPath(std::string path, std::string device)
{
  std::string dataPath = "";
  
  if (!device.empty())
  {
    std::string prefix = "//Devices/Device[@name=\"" + device + "\"]";
    
    if (!path.empty())
    {
      std::istringstream toParse(path);
      std::string token;
      
      // Prefix each part of the path:
      // i.e. "path1|path2" => "{prefix}path1|{prefix}path2"
      while (std::getline(toParse, token, '|'))
      {
        dataPath += prefix + token + "|";
      }
      
      // Get rid of last extraneous '|'
      dataPath.erase(dataPath.length()-1);
    }
    else
    {
      dataPath = prefix;
    }
  }
  else
  {
    dataPath = (!path.empty()) ? path : "//Devices/Device";
  }
  
  return dataPath;
}

std::list<DataItem *> Agent::getDataItems(std::string path, xmlpp::Node * node)
{
  std::list<DataItem *> items;
  
  node = (node == NULL) ? mConfig->getRootNode() : node;
  
  xmlpp::NodeSet elements = node->find(path);
  
  for (unsigned int i=0; i<elements.size(); i++)
  {
    const xmlpp::Element * nodeElement;
    nodeElement = dynamic_cast<const xmlpp::Element*>(elements[i]);
    if (nodeElement)
    {
      std::string nodename = nodeElement->get_name();
      if (nodeElement->get_name() == "DataItem")
      {
        DataItem * item;
        item = getDataItemByName(nodeElement->get_attribute_value("name"));
        if (item != NULL)
        {
          items.push_back(item);
        }
        else
        {
          std::cerr << "DATA ITEM NOT FOUND\n";
        }
      }
      else if (nodename == "Components" or nodename == "DataItems")
      {
        std::list<DataItem *> toMerge = getDataItems("*", elements[i]);
        items.merge(toMerge);
      }
      else // Hopefully "Component"
      {
        std::list<DataItem *> toMerge;
        toMerge = getDataItems("Components/*|DataItems/*", elements[i]);
        items.merge(toMerge);
      }
    }
  }
  
  return items;
}


bool Agent::handleCall(
    std::ostream& out,
    std::string& result,
    const map_type& queries,
    std::string call,
    std::string device
  )
{
  std::string deviceName;
  if (!device.empty())
  {
    deviceName = device;
  }
  else if (queries.is_in_domain("device"))
  {
    deviceName = queries["device"];
  }
  
  if (call == "current")
  {
    std::string path = queries.is_in_domain("path") ? queries["path"] : "";
    unsigned int freq = queries.is_in_domain("frequency") ?
      atoi(queries["frequency"].c_str()) : 0;
    
    return handleCurrent(out, result, devicesAndPath(path, deviceName), freq);
  }
  else if (call == "probe")
  {
    result = handleProbe(deviceName);
    return true;
  }
  else if (call == "sample")
  {
    std::string path = queries.is_in_domain("path") ?
      queries["path"] : "";
    
    unsigned int count = (queries.is_in_domain("count")) ?
      atoi(queries["count"].c_str()) : 100;
    
    unsigned int freq = (queries.is_in_domain("frequency")) ?
      atoi(queries["frequency"].c_str()) : 0;
    
    unsigned int start;
    if (queries.is_in_domain("start"))
    {
      start = atoi(queries["start"].c_str());
    }
    else if (queries.is_in_domain("from"))
    {
      start = atoi(queries["from"].c_str());
    }
    else
    {
      start = 0;
    }
    
    return handleSample(
        out,
        result,
        devicesAndPath(path, deviceName),
        start,
        count,
        freq
      );
  }
  else
  {
    result = printError(
        "ROUTING_ERROR",
        "The path '/" + call + "' does not exist."
      );
    return true;
  }
}

bool Agent::handleCurrent(
    std::ostream& out,
    std::string& result,
    std::string path,
    unsigned int frequency
  )
{
  std::list<DataItem *> dataItems = getDataItems(path);
  
  if (frequency > 0)
  {
    streamData(out, dataItems, true, frequency);
    return false;
  }
  else
  {
    result = fetchCurrentData(dataItems);
    return true;
  }
}

std::string Agent::handleProbe(std::string name)
{
  std::list<Device *> mDeviceList;
  
  if (name != "")
  {
    Device * device = getDeviceByName(name);
    if (device == NULL)
    {
      return printError(
          "NO_DEVICE",
          "Could not find the device '" + name + "'"
        );
    }
    else
    {
      mDeviceList.push_back(device);
    }
  }
  else
  {
    mDeviceList = mDevices;
  }
  
  unsigned int seq, firstSeq;
  getSequenceNumbers(&seq, &firstSeq);
  
  return XmlPrinter::printProbe(
    mAdapterId,
    SLIDING_BUFFER_SIZE,
    seq,
    mDeviceList
  );
}

bool Agent::handleSample(
    std::ostream& out,
    std::string& result,
    std::string path,
    unsigned int start,
    unsigned int count,
    unsigned int frequency
  )
{
  std::list<DataItem *> dataItems = getDataItems(path);
  if (frequency > 0)
  {
    streamData(out, dataItems, false, frequency, start, count);
    return false;
  }
  else
  {
    result = fetchSampleData(dataItems, start, count);
    return true;
  }
}

void Agent::streamData(
    std::ostream& out,
    std::list<DataItem *> dataItems,
    bool current,
    unsigned int frequency,
    unsigned int start,
    unsigned int count
  )
{
  std::string boundary = "--" + md5(intToString(time(NULL)));
  std::string contentType = "Content-type: text/xml";
  
  while (out.good())
  {
    out << boundary << std::endl;
    out << contentType << std::endl;
    
    std::string content = (current) ?
      fetchCurrentData(dataItems) : fetchSampleData(dataItems, start, count);
    
    out << "Content-length: " << content.length() << std::endl;
    
    out << std::endl;
    out << content;
    
    
    out.flush();
    dlib::sleep(frequency);
  }
}

std::string Agent::fetchCurrentData(std::list<DataItem *> dataItems)
{
  unsigned int seq, firstSeq;
  getSequenceNumbers(&seq, &firstSeq);
  return XmlPrinter::printCurrent(
      mAdapterId,
      SLIDING_BUFFER_SIZE,
      seq,
      firstSeq,
      dataItems
    );
}

std::string Agent::fetchSampleData(
    std::list<DataItem *> dataItems,
    unsigned int start,
    unsigned int count
  )
{
  std::list<ComponentEvent *> results;
  
  mSequenceLock->lock();

  unsigned int seq = mSequence;
  unsigned int firstSeq = (mSequence > SLIDING_BUFFER_SIZE) ?
    SLIDING_BUFFER_SIZE - mSequence : 1;
  
  // START SHOULD BE BETWEEN 0 AND SEQUENCE NUMBER
  start = (start <= firstSeq) ? firstSeq  : start;
  unsigned int end = (count + start >= mSequence) ? mSequence-1 : count+start;
  
  for (unsigned int i = start; i<end; i++)
  {
    // Filter out according to if it exists in the list
    std::string dataName = (*mSlidingBuffer)[i]->getDataItem()->getName();
    if (hasDataItem(dataItems, dataName))
    {
      results.push_back((*mSlidingBuffer)[i]);
    }
    else if (end < mSequence)
    {
      // TODO: increment counter?
      end++;
    }
  }
  
  mSequenceLock->unlock();
  
  return XmlPrinter::printSample(
    mAdapterId,
    SLIDING_BUFFER_SIZE,
    seq,
    firstSeq,
    results
  );
}

Device * Agent::getDeviceByName(std::string name)
{
  for (unsigned int i=0; i<mAdapters.size(); i++)
  {
    std::list<Device *>::iterator device;
    for (device=mDevices.begin(); device!=mDevices.end(); device++)
    {
      if ((*device)->getName() == name)
      {
        return *device;
      }
    }
  }
  
  return NULL;
}

DataItem * Agent::getDataItemByName(std::string name)
{
  std::list<DataItem *>::iterator dataItem;
  for (dataItem = mDataItems.begin(); dataItem!=mDataItems.end(); dataItem++)
  {
    if ((*dataItem)->hasName(name))
    {
      return (*dataItem);
    }
  }
  return NULL;
}

bool Agent::hasDataItem(std::list<DataItem *> dataItems, std::string name)
{
  std::list<DataItem *>::iterator dataItem;
  for (dataItem = dataItems.begin(); dataItem!=dataItems.end(); dataItem++)
  {
    if ((*dataItem)->hasName(name))
    {
      return true;
    }
  }
  return false;
}

void Agent::getSequenceNumbers(unsigned int * seq, unsigned int * firstSeq)
{
  mSequenceLock->lock();
  
  *seq = mSequence;
  *firstSeq = (mSequence > SLIDING_BUFFER_SIZE) ?
    SLIDING_BUFFER_SIZE - mSequence : 1;
  
  mSequenceLock->unlock();
}

std::string Agent::printError(std::string errorCode, std::string text)
{
  return XmlPrinter::printError(1, SLIDING_BUFFER_SIZE, 2, errorCode, text);
}

/***** Procedural Code *****/
void terminateServerThread(Agent * server)
{
  std::cout << "Press enter at anytime to terminate web server" << std::endl;
  std::cin.get();

  // Shut down server by unblocking Agent::start()
  server->clear();
  delete server;
}

int main()
{
  try
  {
    //Agent * agent = new Agent("128.32.164.245", 7878, "../include/new.xml");
    Agent * agent = new Agent(
      "agent.mtconnect.org",
      7878,
      "../include/config_no_namespace.xml",
      2
    );
    
    // create a thread that will listen for the user to end this program
    thread_function t(terminateServerThread, agent);
    
    agent->set_listening_port(Agent::SERVER_PORT);
    agent->start();
  }
  catch (std::exception & e)
  {
    std::cerr << "Agent.cpp main: " << e.what() << std::endl;
  }
  
  return 0;
}
