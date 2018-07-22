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

#include "ipv4-trust-table.h"

namespace ns3 {

Ipv4TrustTable::Ipv4TrustTable ()
{
}

void Ipv4TrustTable::AddRecord (Ipv4TrustEntry entry)
{
//  m_tableRecords.push_back (entry);
}

void Ipv4TrustTable::RemoveRecord (Ipv4TrustEntry entry)
{
//  m_tableRecords.pop_back (); //need to change this
}

void Ipv4TrustTable::UpdateRecord (Ipv4TrustEntry entry)
{
  // TODO write update trust record logic
}

bool Ipv4TrustTable::LookupTrustEntry (Ipv4Address dst,
                                       Ipv4TrustEntry & tt)
{
  if (m_tableRecords.empty ())
    {
      std::cout<<"Trust entry to " << dst << " not found; trust table is empty";
      return false;
    }
  std::map<Ipv4Address, Ipv4TrustEntry>::const_iterator i = m_tableRecords.find (dst);
  if (i == m_tableRecords.end ())
    {
      std::cout<<"Trust entry to " << dst << " not found";
      return false;
    }
  tt = i->second;
  std::cout<<"Trust entry to " << dst << " found";
  return true;
}

Ipv4TrustTable::~Ipv4TrustTable ()
{
}

} // namespace ns3
