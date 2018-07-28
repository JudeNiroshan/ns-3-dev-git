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

#ifndef TRUSTTABLE_H_
#define TRUSTTABLE_H_

#include "trust-entry.h"
#include "ns3/address.h"
#include <map>

using std::map;

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
 * \brief Trust table for the a network node
 */
class TrustTable
{

private:
  /**
   * \brief m_tableRecords type of <Ipv4Address, Ipv4TrustEntry> classes
   * contains here representing the IPv4 trust table rows
   */
  std::map<Address, TrustEntry> m_tableRecords;

public:
  TrustTable ();
  virtual ~TrustTable ();

  /**
   * \brief Add a new record to the Trust Table
   * \param [in] entry The new entry.
   */
  void AddRecord (TrustEntry entry);

  /**
   * \brief Remove a record from the Trust Table
   * \param [in] entry The entry to be removed.
   */
  void RemoveRecord (TrustEntry entry);

  /**
   * \brief Update a record of the Trust Table
   * \param [in] entry The entry to be modified.
   */
  void UpdateRecord (TrustEntry entry);

  /**
   * Lookup trust table entry with destination address dst
   * \param dst destination address
   * \param tt entry with destination address dst, if exists
   * \return true on success
   */
  bool LookupTrustEntry (Address dst, TrustEntry & tt);


  /**
   * \brief add a new trust table entry or update the existing
   * trust table entry for the given Address
   * \param dst Address instance of target node
   * \param trustValue trust value
   */
  void AddOrUpdateTrustTableEntry (Address dst,
                                   double trustValue);
};

} // namespace ns3

#endif
