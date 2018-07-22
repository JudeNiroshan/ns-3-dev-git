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

#ifndef SIMPLE_AODV_TRUST_HANDLER_H_
#define SIMPLE_AODV_TRUST_HANDLER_H_

#include "ns3/ipv4-trust-handler.h"
#include "aodv-trust-entry.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv4-routing-protocol.h"
#include "ns3/ipv4-routing-helper.h"

namespace ns3 {
namespace aodv {

/**
 * \ingroup internet
 * \defgroup trust Trust management framework.
 *
 * The Trust Management Framework is built-in support to implement custom
 * trust based protocols in ns-3.
 */

/**
 * \ingroup trust
 * \brief The aodv specific trust operations handler
 */
class SimpleAodvTrustHandler : public Ipv4TrustHandler
{
private:
  /**
   * \brief map of AodvTrustEntry that contain runtime trust metrics
   * for each directly connected nodes
   */
  std::map<Ipv4Address, AodvTrustEntry> m_trustParameters;

public:
  static TypeId GetTypeId (void);

  SimpleAodvTrustHandler ();
  virtual ~SimpleAodvTrustHandler ();

  /**
   * \brief Promiscuous callback function which will hooked for nodes.
   * this function will be called upon a packet is being received to the node.
   * \returns bool true if the callback handle the packet successfully
   */
  bool OnReceivePromiscuousCallback (Ptr<NetDevice> device,
                                     Ptr<const Packet> packet,
                                     uint16_t protocol,
                                     const Address &from,
                                     const Address &to,
                                     NetDevice::PacketType packetType);

  /**
   * \brief Calculate the trust value for a given destination node
   * \param [in] address target node IPv4 address to calculate the trust
   * \returns int32_t trust value
   */
  int32_t calculateTrust (Address address);

  /**
   * \brief Hook the promiscuous callback to the aggregated
   * node object
   */
  void AttachPromiscuousCallbackToNode ();

};

}
} // namespace ns3
#endif
