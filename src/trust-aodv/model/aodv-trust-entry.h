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

#ifndef AODV_TRUST_ENTRY_H_
#define AODV_TRUST_ENTRY_H_

#include "ns3/core-module.h"

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
 * \brief The aodv specific trust entry object which represent rows in trust table.
 */
class AodvTrustEntry
{
private:
  // number of rreq messages
  uint16_t rreq;
  // number of reply messages
  uint16_t rply;
  // number of error message
  uint16_t err;
  // number of hello message
  uint16_t hello;

public:
  AodvTrustEntry ();
  virtual ~AodvTrustEntry ();

  /**
   * \brief Returns the error count of trust table entry
   * \returns uint16_t of the error count
   */
  uint16_t GetErr () const;

  /**
   * \brief Set the error count of trust table entry
   * \param [in] err uint16_t of the error count
   */
  void SetErr (uint16_t err);

  /**
   * \brief Returns the hello count of trust table entry
   * \returns uint16_t of the hello count
   */
  uint16_t GetHello () const;

  /**
   * \brief Set the hello packet count of trust table entry
   * \param [in] hello uint16_t of the hello packet count
   */
  void SetHello (uint16_t hello);

  /**
   * \brief Returns the reply count of trust table entry
   * \returns uint16_t of the reply count
   */
  uint16_t GetRply () const;

  /**
   * \brief Set the reply count of trust table entry
   * \param [in] reply uint16_t of the reply count
   */
  void SetRply (uint16_t rply);

  /**
   * \brief Returns the rreq count of trust table entry
   * \returns uint16_t of the rreq count
   */
  uint16_t GetRreq () const;

  /**
   * \brief Set the rreq count of trust table entry
   * \param [in] rreq uint16_t of the rreq count
   */
  void SetRreq (uint16_t rreq);

};
  std::ostream &operator<< (std::ostream &os, AodvTrustEntry const &m);

} // namespace ns3
#endif
