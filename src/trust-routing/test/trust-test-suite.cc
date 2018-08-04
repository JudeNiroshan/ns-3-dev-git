/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

// Include a header file from your module to test.
#include "ns3/trust-table.h"

// An essential include is test.h
#include "ns3/test.h"
#include "ns3/ipv4-header.h"

// Do not put your test classes in namespace ns3.  You may find it useful
// to use the using directive to access the ns3 namespace directly
using namespace ns3;

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

