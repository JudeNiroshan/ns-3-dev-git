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

#include <vector>
#include "abstract-trust-entry.h"

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
 * \brief The abstract Trust table for the nodes.
 */
class TrustTable
{

private:
  std::vector<AbstractTrustEntry> m_tableRecords;
public:
  TrustTable ();
  virtual ~TrustTable ();

  /**
   * \brief Add a new record to the Trust Table
   * \param [in] entry The new entry.
   */
  void AddRecord (AbstractTrustEntry entry);

  /**
   * \brief Remove a record from the Trust Table
   * \param [in] entry The entry to be removed.
   */
  void RemoveRecord (AbstractTrustEntry entry);

  /**
   * \brief Update a record of the Trust Table
   * \param [in] entry The entry to be modified.
   */
  void UpdateRecord (AbstractTrustEntry entry);
};

} // namespace ns3

#endif
