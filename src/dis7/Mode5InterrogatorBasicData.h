#pragma once

#include <dis7/PduSuperclass.h>
#include <dis7/EntityID.h>
#include <utils/DataStream.h>
#include <dis7/msLibMacro.h>

namespace DIS {

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All
// rights reserved.
//
// @author Alessio Iannone, quonn77@gmail.com
class EXPORT_MACRO Mode5InterrogatorBasicData {
 public:
  Mode5InterrogatorBasicData();
  virtual ~Mode5InterrogatorBasicData();
  virtual void marshal(DataStream& dataStream) const;
  virtual void unmarshal(DataStream& dataStream);
  virtual int getMarshalledSize() const;

  bool operator==(const Mode5InterrogatorBasicData& rhs) const;

  unsigned char getM5InterrogatorStatus();
  void setM5InterrogatorStatus(unsigned char status);

  unsigned int getM5MessageFormatPresent();
  void setM5MessageFormatPresent(unsigned int m5MessageFormatPresent);

  EntityID& getInterrogatedEntityID();
  const EntityID& getInterrogatedEntityID() const;
  void setInterrogatedEntityID(const EntityID& entityID);

 protected:
  unsigned char _m5InterrogatorStatus;
  unsigned char _padding1;
  unsigned short _padding2;

  /**
   *  This field shall indicate the Mode 5 Message Formats supported
   * by this Mode 5 interrogator. See B.2.28 for requirements related to setting
   * this field for a Mode 5 interrogator. This field shall be represented by a
   * Mode 5 Message Formats record.
   *
   * This record shall be included in the Mode 5 Message Formats Present field
   * of the Mode 5 Transponder Basic Data record and also the Mode 5
   * Interrogator Basic Data record contained in Layer 3. This is a 32-bit
   * record. The fields of this record are as follows: — Message Formats 0
   * to 31. Each bit shall represent a specific message format as shown in Table
   * B.32. It shall be represented by an enumeration as follows: Not Present (0)
   * and Present (1)
   */
  unsigned int _m5MessageFormatPresent;

  /**
   * This field shall specify the Entity ID of the entity to which the
   * interrogation is being directed. It shall be represented by an Entity ID
   * record (page 548)
   */
  EntityID _interrogatedEntityID;

  /// Unused
  unsigned short _padding3;
};
}  // namespace DIS
// Copyright (c) 1995-2009 held by the author(s).  All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
//  are met:
//
//  * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// * Neither the names of the Naval Postgraduate School (NPS)
//  Modeling Virtual Environments and Simulation (MOVES) Institute
// (http://www.nps.edu and http://www.MovesInstitute.org)
// nor the names of its contributors may be used to endorse or
//  promote products derived from this software without specific
// prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// AS IS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
