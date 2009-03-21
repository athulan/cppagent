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

#include "xml_printer.hpp"

/* XmlPrinter public methods */
XmlPrinter::XmlPrinter(std::ostringstream * xmlStream)
{
  mXmlStream = xmlStream;
  try
  {
    initErrorXml();
    initSampleXml();
  }
  catch (std::exception & e)
  {
    std::cout << "XML Exception: " << e.what() << std::endl;
  }
}

XmlPrinter::~XmlPrinter()
{
  delete mErrorXml;
  delete mSampleXml;
}


void XmlPrinter::printNode(const xmlpp::Node* node, unsigned int indentation)
{
  // Constant node data determined for each node
  const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
  const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(node);
  const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(node);
  const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(node);

  // Ignore empty whitespace
  if (nodeText and nodeText->is_white_space())
  {
    return;
  }
  
  Glib::ustring nodename = node->get_name();
  
  // Node name tag: i.e. "<tag"
  // Leave ">" out in case there are other attributes
  if (!nodeText and !nodeComment and !nodename.empty())
  {
    printIndentation(indentation);
    *mXmlStream << "<" << nodename;
  }
  
  // Right now, nothing is being done for conditions: if nodeContent/nodeComment
  if (nodeText)
  {
    printIndentation(indentation);
    *mXmlStream << nodeText->get_content() << std::endl;
  }
  else if (nodeElement)
  {
    // Print attributes for the element
    // i.e. ...attribute1="value1" attribute2="value2"...
    const xmlpp::Element::AttributeList& attributes = nodeElement->get_attributes();
    for (xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
    {
      const xmlpp::Attribute* attribute = *iter;
      *mXmlStream << " " << attribute->get_name() << "=\"" << attribute->get_value() << "\"";
    }
    
    std::string endTag = (nodeElement->has_child_text() or indentation == 0) ? ">" : " />";
    
    *mXmlStream << endTag << std::endl;
  }
  
  // If node does NOT have content, then it may have children, so perform print on children
  if (!nodeContent)
  {
    // Recurse through child nodes
    xmlpp::Node::NodeList list = node->get_children();
    for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter)
    {
      printNode(*iter, indentation + 2);
    }
  }
  
  // Close off xml tag, i.e. </tag>
  if ((!nodeText and !nodeComment and !nodename.empty() and nodeElement->has_child_text()) or indentation == 0)
  {
    printIndentation(indentation);
    *mXmlStream << "</" << nodename << ">" << std::endl;
  }
}

void XmlPrinter::printError(
    unsigned int adapterId,
    unsigned int bufferSize,
    unsigned int nextSeq,
    std::string errorCode,
    std::string errorText
  )
{  
  char timeBuffer [TIME_BUFFER_SIZE];
  getCurrentTime(timeBuffer);
  
  xmlpp::Element * header = mErrorXml->get_root_node()->add_child("Header");
  header->set_attribute("creationTime", timeBuffer);
  header->set_attribute("sender", "localhost");
  header->set_attribute("instanceId", intToString(adapterId));
  header->set_attribute("bufferSize", intToString(bufferSize));
  header->set_attribute("version", MTCONNECT_XML_VERS);
  header->set_attribute("nextSequence", intToString(nextSeq));
  
  xmlpp::Element * error = mErrorXml->get_root_node()->add_child("Error");
  error->set_attribute("errorCode", errorCode);
  error->set_child_text(errorText);
  
  
  printNode(mErrorXml->get_root_node());
  
  mErrorXml->get_root_node()->remove_child(header);
  mErrorXml->get_root_node()->remove_child(error);
}

void XmlPrinter::printSample(
    unsigned int adapterId,
    unsigned int bufferSize,
    unsigned int nextSeq,
    unsigned int firstSeq,
    std::vector<Device *> devices
  )
{
  char timeBuffer [TIME_BUFFER_SIZE];
  getCurrentTime(timeBuffer);
  
  xmlpp::Element * header = mSampleXml->get_root_node()->add_child("Header");
  header->set_attribute("creationTime", timeBuffer);
  header->set_attribute("sender", "localhost");
  header->set_attribute("instanceId", intToString(adapterId));
  header->set_attribute("bufferSize", intToString(bufferSize));
  header->set_attribute("version", MTCONNECT_XML_VERS);
  header->set_attribute("nextSequence", intToString(nextSeq));
  header->set_attribute("firstSequence", intToString(firstSeq));
  header->set_attribute("lastSequence", intToString(nextSeq - 1));
  
  xmlpp::Element * streams = mSampleXml->get_root_node()->add_child("Streams");
  
  printNode(mSampleXml->get_root_node());
  
  mErrorXml->get_root_node()->remove_child(header);
}

/* XmlPrinter Protected Methods */
void XmlPrinter::initErrorXml()
{
  mErrorXml = new xmlpp::Document;
  
  xmlpp::Element * root = mErrorXml->create_root_node("MTConnectStreams");
  
  root->set_attribute("xmlns:m", "urn:mtconnect.com:MTConnectError:1.0");
  root->set_attribute("xmlns", "urn:mtconnect.com:MTConnectError:1.0");
  root->set_attribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
  root->set_attribute("xsi:schemaLocation", "urn:mtconnect.com:MTConnectError:1.0 /schemas/MTConnectError.xsd");
}

void XmlPrinter::initSampleXml()
{
  mSampleXml = new xmlpp::Document;
  
  xmlpp::Element * root = mSampleXml->create_root_node("MTConnectStreams");
  
  root->set_attribute("xmlns:m", "urn:mtconnect.com:MTConnectStreams:1.0");
  root->set_attribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
  root->set_attribute("xmlns", "urn:mtconnect.com:MTConnectError:1.0");
  root->set_attribute("xsi:schemaLocation", "urn:mtconnect.com:MTConnectError:1.0 /schemas/MTConnectError.xsd");
}

void XmlPrinter::printIndentation(unsigned int indentation)
{
  for(unsigned int i = 0; i < indentation; ++i)
  {
    *mXmlStream << " ";
  }
}

void XmlPrinter::getCurrentTime(char buffer[])
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = gmtime ( &rawtime );

  strftime (buffer, TIME_BUFFER_SIZE, "%Y-%m-%dT%H:%M:%S+00:00", timeinfo);
}

std::string XmlPrinter::intToString(unsigned int i)
{
  std::ostringstream stm;
  stm << i;
  return stm.str();
}
