/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2018 Sri Lanka Institute of Information Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Jude Niroshan <jude.niroshan11@gmail.com>
 */

#include "ns3/trust-table.h"
#include "ns3/test.h"
#include "ns3/ipv4-header.h"

namespace ns3 {

/**
 * \ingroup aodv-test
 * \ingroup tests
 *
 * \brief Unit test for AODV routing table
 *      Unit test steps:
 *        - Create an empty trust table
 *        - Call LookupTrustEntry => should return false
 *        - Add a new trust entry to trust table
 *        - Call LookupTrustEntry => should return true
 *        - Update trust value in the trust table
 *        - Call LookupTrustEntry => should return true
 *        - Remove trust entry from the trust table
 *        - Call LookupTrustEntry => should return false
 */
struct TrustTableTest : public TestCase
{
  TrustTableTest () : TestCase ("TrustTable")
  {
  }
  virtual void DoRun ()
  {
    TrustTable trustTable;
    TrustEntry testEntry;
    NS_TEST_EXPECT_MSG_EQ (trustTable.LookupTrustEntry (Ipv4Address ("1.2.3.4"), testEntry), false, "trivial");
    NS_TEST_EXPECT_MSG_EQ (trustTable.AddRecord (Ipv4Address ("1.2.3.4"), 0.456), true, "trivial");
    NS_TEST_EXPECT_MSG_EQ (trustTable.LookupTrustEntry (Ipv4Address ("1.2.3.4"), testEntry), true, "trivial");
    NS_TEST_EXPECT_MSG_EQ (trustTable.UpdateRecord (Ipv4Address ("1.2.3.4"), 0.789), true, "trivial");
    testEntry.SetTrustValue (0.789);
    NS_TEST_EXPECT_MSG_EQ (trustTable.LookupTrustEntry (Ipv4Address ("1.2.3.4"), testEntry), true, "trivial");
    NS_TEST_EXPECT_MSG_EQ (trustTable.RemoveRecord (Ipv4Address ("1.2.3.4")), true, "trivial");
    NS_TEST_EXPECT_MSG_EQ (trustTable.LookupTrustEntry (Ipv4Address ("1.2.3.4"), testEntry), false, "trivial");

  }
};

// The TestSuite class names the TestSuite, identifies what type of TestSuite,
// and enables the TestCases to be run.  Typically, only the constructor for
// this class must be defined
//
class TrustTestSuite : public TestSuite
{
public:
  TrustTestSuite ();
};

TrustTestSuite::TrustTestSuite ()
  : TestSuite ("trust-routing", UNIT)
{
  // TestDuration for TestCase can be QUICK, EXTENSIVE or TAKES_FOREVER
  AddTestCase (new TrustTableTest, TestCase::QUICK);
}

// Do not forget to allocate an instance of this TestSuite
static TrustTestSuite trustTestSuite;

}

