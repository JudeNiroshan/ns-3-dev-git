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

#include "aodv-trust-entry.h"

namespace ns3
{

AodvTrustEntry::AodvTrustEntry ()
{
}

AodvTrustEntry::~AodvTrustEntry ()
{
}

uint16_t AodvTrustEntry::GetError () const
{
  return m_error;
}

void AodvTrustEntry::SetError (uint16_t err)
{
  m_error = err;
}

uint16_t AodvTrustEntry::GetHello () const
{
  return m_hello;
}

void AodvTrustEntry::SetHello (uint16_t hello)
{
  m_hello = hello;
}

uint16_t AodvTrustEntry::GetReply () const
{
  return m_reply;
}

void AodvTrustEntry::SetReply (uint16_t rply)
{
  m_reply = rply;
}

uint16_t AodvTrustEntry::GetRreq () const
{
  return m_rreq;
}

void AodvTrustEntry::SetRreq (uint16_t rreq)
{
  m_rreq = rreq;
}

std::ostream &operator<< (std::ostream &os, AodvTrustEntry const &m)
{
  os << "rreq=" << m.GetRreq() << "|" << "rrep=" << m.GetReply();
  return os;
}

}
