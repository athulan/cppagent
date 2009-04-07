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

#include "device_test.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(DeviceTest);

void DeviceTest::setUp()
{
  std::map<std::string, std::string> attributes1;
  attributes1["id"] = 3;
  attributes1["name"] = "DeviceTestA";
  attributes1["uuid"] = "UniversalUniqueIdA";
  attributes1["sampleRate"] = 100.11;
  attributes1["iso841Class"] = 12;
  
  a = new Device(attributes1);
  
  std::map<std::string, std::string> attributes2;
  attributes2["id"] = 5;
  attributes2["name"] = "DeviceTestB";
  attributes2["uuid"] = "UniversalUniqueIdB";
  attributes2["iso841Class"] = 24;
  
  b = new Device(attributes2);
}

void DeviceTest::tearDown()
{
  delete a;
  delete b;
}

void DeviceTest::testGetAttributes()
{
  std::map<std::string, std::string> attributes1 = a->getAttributes();
  CPPUNIT_ASSERT_EQUAL(attributes1["id"], 3);
  CPPUNIT_ASSERT_EQUAL(attributes1["name"], "DeviceTestA");
  CPPUNIT_ASSERT_EQUAL(attributes1["uuid"], "UniversalUniqueIdA");
  CPPUNIT_ASSERT_EQUAL(attributes1["sampleRate"], 100.11);
  CPPUNIT_ASSERT_EQUAL(attributes1["iso841Class"], 12);
  
  std::map<std::string, std::string> attributes2 = b->getAttributes();
  CPPUNIT_ASSERT_EQUAL(attributes2["id"], 5);
  CPPUNIT_ASSERT_EQUAL(attributes2["name"], "DeviceTestB");
  CPPUNIT_ASSERT_EQUAL(attributes2["uuid"], "UniversalUniqueIdB");
  CPPUNIT_ASSERT_EQUAL(attributes2["sampleRate"], 0.0);
  CPPUNIT_ASSERT_EQUAL(attributes2["iso841Class"], 24);
}

void DeviceTest::testGetClass()
{
  CPPUNIT_ASSERT_EQUAL("Device", a->getClass());
  CPPUNIT_ASSERT_EQUAL("Device", b->getClass());
}

