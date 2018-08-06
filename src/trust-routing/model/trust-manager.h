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

#ifndef TRUSTMANAGER_H_
#define TRUSTMANAGER_H_

#include "ns3/application.h"
#include "ns3/node.h"
#include "ns3/address.h"
#include "trust-table.h"

namespace ns3 {

class TrustManager : public Application
{

  /**
   * \ingroup trust
   * \defgroup trust Trust management framework.
   *
   * The Trust Management Framework is built-in support to implement custom
   * trust based protocols in ns-3.
   */

  /**
   * \ingroup trust
   * \brief Generic class for trust framework
   */
public:

  /**
   * \brief trust table which holds trust values for directly connected nodes.
   * this will be used for trust framework to transform a protocol into a
   * trust based variation
   */
  TrustTable m_trustTable;

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  TrustManager ();
  virtual ~TrustManager ();


  /**
   * \brief prints the trust table at a particular time.
   * \param printTime the time at which the trust table is supposed to be printed.
   * \param stream The output stream object to use
   * \param unit The time unit to be used in the report
   *
   * This method calls the Print() method of the TrustManager at the
   * specified time; the output format is trust table-specific.
   */
  // static void PrintTrustTableAt (Time printTime, Ptr<OutputStreamWrapper> stream, Time::Unit unit = Time::S);

#ifdef NOTYET
  /**
   * \brief calculate the trust value for a given IPv4 address host
   * with in the network simulation
   * \param address Address instance of target node
   * \Return double type of trust value
   */
  virtual double calculateTrust (Address ipv4Address) = 0;
#endif

private:
  /**
   * \brief prints the trust table
   * \param stream The output stream object to use
   *
   * This method calls the Print() method of the TrustTable at the
   * specified time; the output format is trust table-specific.
   */
  // static void Print (Ptr<OutputStreamWrapper> stream);
};

} // namespace ns3

#endif
