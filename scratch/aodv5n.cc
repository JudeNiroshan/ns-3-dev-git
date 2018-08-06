/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 IITP RAS
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
 * This is an example script for AODV manet routing protocol. 
 *
 * Authors: Pavel Boyko <boyko@iitp.ru>
 */

#include <iostream>
#include <cmath>
#include "ns3/aodv-module.h"
#include "ns3/netanim-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/wifi-module.h" 
#include "ns3/v4ping-helper.h"
#include "ns3/on-off-helper.h"
#include "ns3/csma-helper.h"
#include "ns3/simple-aodv-trust-manager.h"

using namespace ns3;
using namespace aodv;

/**
 * \ingroup aodv-examples
 * \ingroup examples
 * \brief Test script.
 * 
 * This is non-linear simulation of 5 nodes with static positions
 */
class AodvExample 
{
public:
  AodvExample ();
  /**
   * \brief Configure script parameters
   * \param argc is the command line argument count
   * \param argv is the command line arguments
   * \return true on successful configuration
  */
  bool Configure (int argc, char **argv);
  /// Run simulation
  void Run ();
  /**
   * Report results
   * \param os the output stream
   */
  void Report (std::ostream & os);

private:

  // parameters
  /// Number of nodes
  uint32_t size;
  /// Distance between nodes, meters
  double step;
  /// Simulation time, seconds
  double totalTime;
  /// Write per-device PCAP traces if true
  bool pcap;
  /// Print routes if true
  bool printRoutes;

  // network
  /// nodes used in the example
  NodeContainer nodes;
  /// devices used in the example
  NetDeviceContainer devices;
  /// interfaces used in the example
  Ipv4InterfaceContainer interfaces;

private:
  /// Create the nodes
  void CreateNodes ();
  /// Create the devices
  void CreateDevices ();
  /// Create the network
  void InstallInternetStack ();
  /// Create the simulation applications
  void InstallApplications ();
  /// Enable trust framework for all nodes
  void InstallTrustFramework ();
};

int main (int argc, char **argv)
{
  AodvExample test;
  if (!test.Configure (argc, argv))
    NS_FATAL_ERROR ("Configuration failed. Aborted.");

  test.Run ();
  test.Report (std::cout);
  return 0;
}

//-----------------------------------------------------------------------------
AodvExample::AodvExample () :
  size (5),
  step (100),
  totalTime (100),
  pcap (true),
  printRoutes (true)
{
}

bool
AodvExample::Configure (int argc, char **argv)
{
  // Enable AODV logs by default. Comment this if too noisy
  // LogComponentEnable("AodvRoutingProtocol", LOG_LEVEL_ALL);

  SeedManager::SetSeed (12345);
  CommandLine cmd;

  cmd.AddValue ("pcap", "Write PCAP traces.", pcap);
  cmd.AddValue ("printRoutes", "Print routing table dumps.", printRoutes);
  cmd.AddValue ("size", "Number of nodes.", size);
  cmd.AddValue ("time", "Simulation time, s.", totalTime);
  cmd.AddValue ("step", "Grid step, m", step);

  cmd.Parse (argc, argv);
  return true;
}

void
AodvExample::Run ()
{
//  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", UintegerValue (1)); // enable rts cts all the time.
  CreateNodes ();
  CreateDevices ();
  InstallInternetStack ();
  InstallApplications ();
  InstallTrustFramework ();

  std::cout << "Starting simulation for " << totalTime << " s ...\n";

  Simulator::Stop (Seconds (totalTime));

  AnimationInterface anim ("aodv5n.xml"); // Mandatory
  AnimationInterface::SetConstantPosition (nodes.Get (0), 0, 40000);
  AnimationInterface::SetConstantPosition (nodes.Get (1), 20000, 30000);
  AnimationInterface::SetConstantPosition (nodes.Get (2), 20000, 50000);
  AnimationInterface::SetConstantPosition (nodes.Get (3), 50000, 40000);
  AnimationInterface::SetConstantPosition (nodes.Get (4), 40000, 35000);
  anim.UpdateNodeSize (0, 5000, 5000);
  anim.UpdateNodeSize (1, 5000, 5000);
  anim.UpdateNodeSize (2, 5000, 5000);
  anim.UpdateNodeSize (3, 5000, 5000);
  anim.UpdateNodeSize (4, 5000, 5000);
  anim.EnablePacketMetadata(true);

  Simulator::Run ();
  Simulator::Destroy ();
}

void
AodvExample::Report (std::ostream &)
{ 
}

void
AodvExample::CreateNodes ()
{
  std::cout << "Creating " << (unsigned)size << " nodes " << step << " m apart.\n";
  nodes.Create (size);
  // Name nodes
  for (uint32_t i = 0; i < size; ++i)
    {
      std::ostringstream os;
      os << "node-" << i;
      Names::Add (os.str (), nodes.Get (i));
    }
  // Create static grid
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject <ListPositionAllocator>();
  positionAlloc ->Add(Vector(1000, 0, 0)); // node0
  positionAlloc ->Add(Vector(2000, 0, 0)); // node1
  positionAlloc ->Add(Vector(4500, 0, 0)); // node2
  positionAlloc ->Add(Vector(5500, 0, 0)); // node3
  positionAlloc ->Add(Vector(6500, 0, 0)); // node4
  mobility.SetPositionAllocator(positionAlloc);
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (nodes);
}

void
AodvExample::CreateDevices ()
{
  CsmaHelper csma;

  devices = csma.Install (nodes);
//  AsciiTraceHelper ascii;
//  csma.EnableAsciiAll (ascii.CreateFileStream ("aodv5n.tr"));

  if (pcap)
    {
      csma.EnablePcapAll (std::string ("aodv"));
    }

  /*WifiMacHelper wifiMac;
  wifiMac.SetType ("ns3::AdhocWifiMac");
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
  wifiPhy.SetChannel (wifiChannel.Create ());
  WifiHelper wifi;
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager", "DataMode", StringValue ("OfdmRate6Mbps"), "RtsCtsThreshold", UintegerValue (0));
  devices = wifi.Install (wifiPhy, wifiMac, nodes);

  if (pcap)
    {
      wifiPhy.EnablePcapAll (std::string ("aodv"));
    }*/
}

void
AodvExample::InstallInternetStack ()
{
  AodvHelper aodv;
  // you can configure AODV attributes here using aodv.Set(name, value)
  InternetStackHelper stack;
  stack.SetRoutingHelper (aodv); // has effect on the next Install ()
  stack.Install (nodes);
  Ipv4AddressHelper address;
  address.SetBase ("10.0.0.0", "255.0.0.0");
  interfaces = address.Assign (devices);

  if (printRoutes)
    {
      Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> ("aodv.routes", std::ios::out);
      aodv.PrintRoutingTableAllAt (Seconds (8), routingStream);
    }
}

void
AodvExample::InstallApplications ()
{
  /*uint16_t port = 9;   // Discard port (RFC 863)

  OnOffHelper onoff ("ns3::UdpSocketFactory",
                         InetSocketAddress (interfaces.GetAddress (size - 1), port));
  onoff.SetConstantRate (DataRate ("448kb/s"));

  ApplicationContainer apps = onoff.Install (nodes.Get (0));
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (100.0));
*/
  V4PingHelper ping (interfaces.GetAddress (size - 1));
  ping.SetAttribute ("Verbose", BooleanValue (true));

  ApplicationContainer p = ping.Install (nodes.Get (0));
  p.Start (Seconds (0));
  p.Stop (Seconds (totalTime) - Seconds (0.001));

  // move node away
  Ptr<Node> node = nodes.Get (size/2);
  Ptr<MobilityModel> mob = node->GetObject<MobilityModel> ();
  Simulator::Schedule (Seconds (totalTime/3), &MobilityModel::SetPosition, mob, Vector (1e5, 1e5, 1e5));
}

void
AodvExample::InstallTrustFramework ()
{
  for (uint32_t i = 0; i < size; ++i)
    {
      Ptr<SimpleAodvTrustManager> simpleAodvTrustManager = CreateObject<SimpleAodvTrustManager>();
      nodes.Get(i)->AddApplication (simpleAodvTrustManager);
    }
}
