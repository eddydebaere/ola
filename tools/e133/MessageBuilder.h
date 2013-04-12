/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * MessageBuilder.h
 * Copyright (C) 2013 Simon Newton
 *
 * A class to simplify some of the E1.33 packet building operations.
 */

#ifndef TOOLS_E133_MESSAGEBUILDER_H_
#define TOOLS_E133_MESSAGEBUILDER_H_

#include <ola/io/IOStack.h>
#include <ola/io/MemoryBlockPool.h>
#include <string>

#include "plugins/e131/e131/CID.h"
#include "plugins/e131/e131/E133Enums.h"

using ola::plugin::e131::CID;
using std::string;

/**
 * Provides helper methods for common E1.33 packet construction operations.
 */
class MessageBuilder {
  public:
    MessageBuilder(const CID &cid, const string &source_name);
    ~MessageBuilder() {}

    void BuildNullTCPPacket(ola::io::IOStack *packet);

    void BuildTCPE133StatusPDU(ola::io::IOStack *packet,
                               uint32_t sequence_number, uint16_t endpoint_id,
                               ola::plugin::e131::E133StatusCode status_code,
                               const string &description);
    void BuildUDPE133StatusPDU(ola::io::IOStack *packet,
                               uint32_t sequence_number, uint16_t endpoint_id,
                               ola::plugin::e131::E133StatusCode status_code,
                               const string &description);

    void BuildTCPRootE133(ola::io::IOStack *packet, uint32_t vector,
                          uint32_t sequence_number, uint16_t endpoint_id);
    void BuildUDPRootE133(ola::io::IOStack *packet, uint32_t vector,
                          uint32_t sequence_number, uint16_t endpoint_id);

    ola::io::MemoryBlockPool *pool() { return &m_memory_pool; }

  private:
    const CID m_cid;
    const string m_source_name;
    ola::io::MemoryBlockPool m_memory_pool;
};
#endif  // TOOLS_E133_MESSAGEBUILDER_H_