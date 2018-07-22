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

#include "ipv4-trust-entry.h"

namespace ns3 {

Ipv4TrustEntry::Ipv4TrustEntry ()
{
}

Ipv4TrustEntry::~Ipv4TrustEntry ()
{
}

Ipv4Address Ipv4TrustEntry::GetNeighbourAddress ()
{
  return this->m_neighbourAddress;
}

void Ipv4TrustEntry::SetNeighbourAddress (Ipv4Address neighbourAddress)
{
  this->m_neighbourAddress = neighbourAddress;
}

const Time& Ipv4TrustEntry::GetTimestamp ()
{
  return this->m_timestamp;
}

void Ipv4TrustEntry::SetTimestamp (const Time& timestamp)
{
  this->m_timestamp = timestamp;
}

double Ipv4TrustEntry::GetTrustValue ()
{
  return this->m_trustValue;
}

void Ipv4TrustEntry::SetTrustValue (double trustValue)
{
  this->m_trustValue = trustValue;
}

} // namespace ns3

