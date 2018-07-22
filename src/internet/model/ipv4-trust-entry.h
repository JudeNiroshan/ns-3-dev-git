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

#ifndef IPV4_TRUST_ENTRY_H_
#define IPV4_TRUST_ENTRY_H_

#include "ns3/ipv4-address.h"
#include "ns3/nstime.h"

namespace ns3 {

/**
 * \ingroup internet
 * \defgroup trust Trust management framework.
 *
 * The Trust Management Framework is built-in support to implement custom
 * trust based protocols in ns-3.
 */

/**
 * \ingroup trust
 * \brief The entry object which represent a row in trust table.
 */
class Ipv4TrustEntry
{
private:
  // IPv4 address of a neighbour node
  Ipv4Address m_neighbourAddress;
  // trust value for a given neighbour node
  double m_trustValue;
  // Timestamp when the trust value has been set
  Time m_timestamp;

public:
  Ipv4TrustEntry ();
  virtual ~Ipv4TrustEntry ();

  /**
   * \brief Returns the neighbour address of trust table entry
   * \returns the IPv4 address of the neighbour node
   */
  Ipv4Address GetNeighbourAddress ();

  /**
   * \brief Set the neighbour address to trust table entry
   * \param [in] neighbourAddress IPv4 address of neighbour node
   */
  void SetNeighbourAddress (Ipv4Address neighbourAddress);

  /**
   * \brief Get the timestamp of the trust table entry
   * \returns Time object reference represent the m_timestamp
   */
  const Time& GetTimestamp ();

  /**
   * \brief Set the timestamp of the trust table entry
   * \param [in] timestamp Time object reference represent the m_timestamp
   */
  void SetTimestamp (const Time& timestamp);

  /**
   * \brief Get the trust value of the trust table entry
   * \returns double trust value
   */
  double GetTrustValue ();

  /**
   * \brief Set the trust value of the trust table entry
   * \param [in] trustValue double trust value
   */
  void SetTrustValue (double trustValue);
};
} // namespace ns3

#endif
