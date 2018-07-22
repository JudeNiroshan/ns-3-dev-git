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

#include "simple-aodv-trust-handler.h"
#include "ns3/aodv-packet.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("SimpleAodvTrustHandler");
namespace aodv {

NS_OBJECT_ENSURE_REGISTERED(SimpleAodvTrustHandler);

TypeId SimpleAodvTrustHandler::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::aodv::SimpleAodvTrustHandler").SetParent<Object> ().SetGroupName ("Aodv").AddConstructor<
      SimpleAodvTrustHandler> ();
  return tid;
}

SimpleAodvTrustHandler::SimpleAodvTrustHandler ()
{
}

SimpleAodvTrustHandler::~SimpleAodvTrustHandler ()
{
}

bool SimpleAodvTrustHandler::OnReceivePromiscuousCallback (Ptr<NetDevice> device,
                                                           Ptr<const Packet> packet,
                                                           uint16_t protocol,
                                                           const Address &from,
                                                           const Address &to,
                                                           NetDevice::PacketType packetType)
{
  std::cout << "JUDE ADDED FROM THE TRUST FRAMEWORK" << std::endl;

  TypeHeader tHeader;
  packet->PeekHeader (tHeader);
  switch (tHeader.Get ())
    {
    case AODVTYPE_RREQ:
      {
        // increment RREQ count
        tHeader.Print (std::cout);
        break;
      }
    case AODVTYPE_RREP:
      {
        // increment RPLY count
        tHeader.Print (std::cout);
        break;
      }
    case AODVTYPE_RERR:
      {
        // increment ERR count
        tHeader.Print (std::cout);
        break;
      }
    case AODVTYPE_RREP_ACK:
      {
        // increment ERR count
        tHeader.Print (std::cout);
        break;
      }
    }

  NS_LOG_FUNCTION(device << packet << protocol << &from << &to << packetType);
  bool found = false;

  return found;
}

int32_t SimpleAodvTrustHandler::calculateTrust (Address address)
{

  Ipv4Address ipv4Address = Ipv4Address::ConvertFrom (address);
  AodvTrustEntry m_aodvTrustEntry = m_trustParameters[ipv4Address];
/*
  if (m_aodvTrustEntry == NULL)
    {
      return 0;
    }*/
  double trustDouble = m_aodvTrustEntry.GetRply () / m_aodvTrustEntry.GetRreq () * 1.0;

  // Update the value in Trust Table here
//  Ptr<Node> src;
  Ptr<Node> node = GetObject<Node> ();
  Ptr<Ipv4RoutingProtocol> m_ipv4Routing;
  m_ipv4Routing = Ipv4RoutingHelper::GetRouting<Ipv4RoutingProtocol> (node->GetObject<Ipv4> ()->GetRoutingProtocol ());

  std::cout << trustDouble + 1 << std::endl; // to avoid unused variable compilation warning
  return 1;
}

void SimpleAodvTrustHandler::AttachPromiscuousCallbackToNode ()
{
  Ptr<Node> node = GetObject<Node> ();
  node->GetDevice (0)->SetPromiscReceiveCallback (ns3::MakeCallback (&SimpleAodvTrustHandler::OnReceivePromiscuousCallback,
                                                                     this));
}

}

}
