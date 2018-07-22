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

#ifndef TRUSTHANDLER_H_
#define TRUSTHANDLER_H_

#include "ns3/object.h"

namespace ns3 {

class TrustHandler : public Object
{

  /**
   * \ingroup internet
   * \defgroup trust Trust management framework.
   *
   * The Trust Management Framework is built-in support to implement custom
   * trust based protocols in ns-3.
   */

  /**
   * \ingroup trust
   * \brief Intermediate class that used to communicate with trust table
   */
public:
  TrustHandler ();
  virtual ~TrustHandler ();

};

} // namespace ns3

#endif
