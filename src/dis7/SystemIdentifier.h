#pragma once

#include <dis7/msLibMacro.h>
#include <utils/DataStream.h>

namespace DIS {
// The ID of the IFF emitting system. NOT COMPLETE. Section 6.2.86

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved.
//
// @author DMcG, jkg
/**
 * @brief This is the System Type as defined by the UID 82 of the SISO Standar
 *
 *
 */
enum EXPORT_MACRO IFFSystemType {
  Not_Used = 0,
  Mark_X_XII_ATCRBS_Transponder = 1,
  Mark_X_XII_ATCRBS_Interrogator = 2,
  Soviet_Transponder = 3,
  Soviet_Interrogator = 4,
  RRB_Transponder = 5,
  Mark_XIIA_Interrogator = 6,
  Mode_5_Interrogator = 7,
  Mode_S_Interrogator = 8,
  Mark_XIIA_Transponder = 9,
  Mode_5_Transponder = 10,
  Mode_S_Transponder = 11,
  Mark_XIIA_Combined_Interrogator_Transponder = 12,
  Mark_XII_Combined_Interrogator_Transponder = 13,
  TCAS_ACAS_Transceiver = 14
};
class EXPORT_MACRO SystemIdentifier {
 protected:
    /** general type of emitting system, an enumeration */
    unsigned short _systemType;

    /** named type of system, an enumeration */
    unsigned short _systemName;

    /** mode of operation for the system, an enumeration */
    unsigned char _systemMode;

    /** status of this PDU, see section 6.2.15 */
    unsigned char _changeOptions;

 public:
    SystemIdentifier();
    virtual ~SystemIdentifier();

    virtual void marshal(DataStream& dataStream) const;
    virtual void unmarshal(DataStream& dataStream);

    unsigned short getSystemType() const;
    void setSystemType(unsigned short pX);

    unsigned short getSystemName() const;
    void setSystemName(unsigned short pX);

    unsigned char getSystemMode() const;
    void setSystemMode(unsigned char pX);

    unsigned char getChangeOptions() const;
    void setChangeOptions(unsigned char pX);

    virtual int getMarshalledSize() const;

      /**
       * @brief Check Change/options record bit 4
       * 
       * @return true if bit 4 is 0, false if it is an interrogator and bit 4 is 1
       */
    bool isTransponder() const;

    bool operator==(const SystemIdentifier& rhs) const;
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
