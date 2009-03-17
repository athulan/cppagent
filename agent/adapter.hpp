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

#ifndef ADAPTER_HPP
#define ADAPTER_HPP

#include "xml_parser.hpp"

#include <iostream>

#include <map>
#include <vector>

#include "../lib/dlib/sockets.h"
#include "../lib/dlib/sliding_buffer.h"

#include "connector.hpp"
#include "component_event.hpp"

#include "../devices/axes.hpp"
#include "../devices/controller.hpp"
#include "../devices/component.hpp"
#include "../devices/device.hpp"
#include "../devices/data_item.hpp"
#include "../devices/linear.hpp"
#include "../devices/power.hpp"
#include "../devices/spindle.hpp"

using namespace dlib;

class Adapter : public Connector
{
protected:
  /* Keep the configuration information stored */
  XmlParser * mConfig;
  
  /* */
  unsigned int mSequence;
  
  
  /* Array to keep track of all devices */
  std::vector<Axes *> mAxes;
  std::vector<Controller *> mControllers;
  std::vector<Device *> mDevices;
  std::vector<DataItem *> mDataItems;
  std::vector<Linear *> mLinears;
  std::vector<Power *> mPowers;
  std::vector<Spindle *> mSpindles;
  
  dlib::sliding_buffer_kernel_1<ComponentEvent *> * mSlidingBuffer;
  
protected:
  /* Initial method called to call the Devices/* path and begin loading */
  void loadDevices();
  
  /* Main method to process the nodes and return the objects */
  Component * handleComponent(xmlpp::Node * component, Component * parent = NULL);
  
  /* Helper to handle/return each component of the device */
  Component * loadComponent(xmlpp::Node * component, Component::EComponentSpecs spec);
  
  /* Load the data items */
  void loadDataItems(xmlpp::Node * dataItems);
  
  DataItem * getDataItemByName(std::string name);
  
  /* Helper method to perform loading on children and set up relationships */
  void handleChildren(xmlpp::Node * components, Component * parent = NULL);
  
  void addToBuffer(ComponentEvent * event);
  
public:
  /* Load the adapter with the .xml file */
  Adapter(std::string server, unsigned int port, std::string configXml);
  
  /* Destructor */
  ~Adapter();
  
  /* Method used to search data for a unique ID */
  Component * searchDevicesForId(unsigned int id);
  
  /* Inherited method for incoming data from the server */
  void processData(std::string line);
  
  /* Print methods primarily used for debugging */
  void printComponents();
  void printNodesAndChildren(Component * component);
  void printDataItems();
};

#endif
