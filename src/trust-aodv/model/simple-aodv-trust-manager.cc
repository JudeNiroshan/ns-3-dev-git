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

#include "simple-aodv-trust-manager.h"
#include "aodv-trust-entry.h"
#include "ns3/aodv-packet.h"
#include "ns3/ipv4-header.h"
#include "ns3/ipv4-l3-protocol.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("SimpleAodvTrustManager");
namespace aodv {

NS_OBJECT_ENSURE_REGISTERED(SimpleAodvTrustManager);

TypeId SimpleAodvTrustManager::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::aodv::SimpleAodvTrustManager").SetParent<Object> ().SetGroupName ("Aodv").AddConstructor<
      SimpleAodvTrustManager> ();
  return tid;
}

SimpleAodvTrustManager::SimpleAodvTrustManager ()
{
}

SimpleAodvTrustManager::~SimpleAodvTrustManager ()
{
}

bool SimpleAodvTrustManager::OnReceivePromiscuousCallback (Ptr<NetDevice> device,
                                                           Ptr<const Packet> packet,
                                                           uint16_t protocol,
                                                           const Address &from,
                                                           const Address &to,
                                                           NetDevice::PacketType packetType)
{
  std::cout << "JUDE ADDED FROM : " << from << std::endl;

  Ipv4Header ipv4Header;

  if (protocol != Ipv4L3Protocol::PROT_NUMBER)
    {
      return false;
    }
  packet->PeekHeader (ipv4Header);

  Ipv4Address ipv4Address = ipv4Header.GetSource ();
  std::map<Ipv4Address, AodvTrustEntry>::iterator i = m_trustParameters.find (ipv4Address);
  AodvTrustEntry aodvTrustEntry;

  if (i != m_trustParameters.end ())
    {
      aodvTrustEntry = i->second;
    }

  TypeHeader tHeader;
  packet->PeekHeader (tHeader);
  switch (tHeader.Get ())
    {
    case AODVTYPE_RREQ:
      {
        // increment RREQ count
        std::cout << "RREQ captured in Promiscuous callback function" << std::endl;
        aodvTrustEntry.SetRreq (aodvTrustEntry.GetRreq () + 1);
        break;
      }
    case AODVTYPE_RREP:
      {
        // increment RPLY count
        std::cout << "RREP captured in Promiscuous callback function" << std::endl;
        aodvTrustEntry.SetRply (aodvTrustEntry.GetRply () + 1);
        break;
      }
    case AODVTYPE_RERR:
      {
        // increment ERR count
        std::cout << "RERR captured in Promiscuous callback function" << std::endl;
        aodvTrustEntry.SetErr (aodvTrustEntry.GetErr () + 1);
        break;
      }
    case AODVTYPE_RREP_ACK:
      {
        // increment ERR count
        std::cout << "RREP_ACK captured in Promiscuous callback function" << std::endl;
//        aodvTrustEntry.SetErr(aodvTrustEntry.Get + 1);
        break;
      }
    }

  m_trustParameters[ipv4Address] = aodvTrustEntry;
  double calculatedTrust = this->calculateTrust (ipv4Address);

  /* Ptr<Node> node = GetObject<Node> ();
   Ptr<Ipv4RoutingProtocol> m_ipv4Routing;
   m_ipv4Routing = Ipv4RoutingHelper::GetRouting<Ipv4RoutingProtocol> (node->GetObject<Ipv4> ()->GetRoutingProtocol ());*/
  m_trustTable.AddOrUpdateTrustTableEntry (ipv4Address,
                                           calculatedTrust);

  NS_LOG_FUNCTION(device << packet << protocol << &from << &to << packetType);

  return true;
}

double SimpleAodvTrustManager::calculateTrust (Address address)
{
  Ipv4Address ipv4Address = Ipv4Address::ConvertFrom (address);
  std::map<Ipv4Address, AodvTrustEntry>::iterator i = m_trustParameters.find (ipv4Address);

  if (i == m_trustParameters.end ())
    {
      return 0; // <! No existing data to calculate trust
    }

  AodvTrustEntry m_aodvTrustEntry = i->second;
  double trustDouble = m_aodvTrustEntry.GetRply () / m_aodvTrustEntry.GetRreq () * 1.0;

  return trustDouble;
}

void SimpleAodvTrustManager::AttachPromiscuousCallbackToNode ()
{
  Ptr<Node> node = GetObject<Node> ();
  node->GetDevice (0)->SetPromiscReceiveCallback (ns3::MakeCallback (&SimpleAodvTrustManager::OnReceivePromiscuousCallback,
                                                                     this));
}

}

}
