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

#include "xml_parser_test.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(XmlParserTest);

void XmlParserTest::setUp()
{
  try
  {
    a = new XmlParser("../samples/test_config.xml");
  }
  catch (std::exception & e)
  {
    CPPUNIT_FAIL("Could not locate test xml: ../samples/test_config.xml");
  }
}

void XmlParserTest::tearDown()
{
  delete a;
}

void XmlParserTest::testConstructor()
{
  CPPUNIT_ASSERT_THROW(new XmlParser("../samples/badPath.xml"), int);
  CPPUNIT_ASSERT_NO_THROW(new XmlParser("../samples/test_config.xml"));
}

void XmlParserTest::testGetters()
{
  std::list<Device *> devices = a->getDevices();
  CPPUNIT_ASSERT_EQUAL((size_t) 1, devices.size());

  Device *device = devices.front();
  std::list<DataItem*> dataItems;
  std::map<std::string, DataItem*> dataItemsMap = device->getDeviceDataItems();  
  std::map<std::string, DataItem*>::iterator iter;
  for (iter = dataItemsMap.begin(); iter != dataItemsMap.end(); iter++)
  {
    dataItems.push_back(iter->second);
  }
  
  CPPUNIT_ASSERT_EQUAL((size_t) 17, dataItems.size());
  
  
  bool hasExec = false, hasZcom = false;
  
  std::list<DataItem *>::iterator dataItem;
  for (dataItem=dataItems.begin(); dataItem!=dataItems.end(); dataItem++)
  {
    if ((*dataItem)->getId() == "24" and (*dataItem)->getName() == "execution")
    {
      hasExec = true;
    }
    
    if ((*dataItem)->getId() == "19" and (*dataItem)->getName() == "Zcom")
    {
      hasZcom = true;
    }
  }
  
  CPPUNIT_ASSERT(hasExec);
  CPPUNIT_ASSERT(hasZcom);
}

