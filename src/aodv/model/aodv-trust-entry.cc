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

uint16_t AodvTrustEntry::GetErr ()
{
  return this->err;
}

void AodvTrustEntry::SetErr (uint16_t err)
{
  this->err = err;
}

uint16_t AodvTrustEntry::GetHello ()
{
  return this->hello;
}

void AodvTrustEntry::SetHello (uint16_t hello)
{
  this->hello = hello;
}

uint16_t AodvTrustEntry::GetRply ()
{
  return this->rply;
}

void AodvTrustEntry::SetRply (uint16_t rply)
{
  this->rply = rply;
}

uint16_t AodvTrustEntry::GetRreq ()
{
  return this->rreq;
}

void AodvTrustEntry::SetRreq (uint16_t rreq)
{
  this->rreq = rreq;
}

}
