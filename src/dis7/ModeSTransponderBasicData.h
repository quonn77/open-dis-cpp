#pragma once

#include <dis7/EntityID.h>
#include <dis7/PduSuperclass.h>
#include <dis7/msLibMacro.h>
#include <utils/DataStream.h>

namespace DIS {

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All
// rights reserved.
/**
 * @brief Mode S Interrogator Basic Data record, see page 405 of IEEE 1278.1 2012
 * for further details
 * @author Alessio Iannone, quonn77@gmail.com
 */
class EXPORT_MACRO ModeSTransponderBasicData {
 public:
  ModeSTransponderBasicData();
  virtual ~ModeSTransponderBasicData();
  virtual void marshal(DataStream& dataStream) const;
  virtual void unmarshal(DataStream& dataStream);
  virtual int getMarshalledSize() const;

  bool operator==(const ModeSTransponderBasicData& rhs) const;

  unsigned char getModeSTransponderStatus();
  void setModeSTransponderStatus(unsigned char status);

  unsigned char getModeSLevelPresent();
  void setModeSLevelPresent(unsigned char modeSLevelPresent);
  
  unsigned char getAircraftPresentDomain();
  void setAirCraftPresentDomain(unsigned char aircraftPresentDomain);
  
  unsigned long long getAircraftIdentification();
  void setAircraftIdentification(unsigned long long identification);
  
  unsigned int getAircraftAddress();
  void setAircraftAddress(unsigned int address);
  
  unsigned char getAircraftIDType();
  void setAircraftIDType(unsigned char type);

  unsigned char getDAPSource();
  void setDAPSource(unsigned char source);

  unsigned short getModeSAltitude();
  void setModeSAltitude(unsigned short modeSAltitude);

  unsigned char getCapabilityReport();
  void setCapabilityReport(unsigned char capabilityReport);

 protected:
  unsigned char _modeSTransponderStatus;
  unsigned char _modeSLevelPresent;
  unsigned char _aircraftPresentDomain;
  unsigned long long _aircraftIdentification; //64 bit
  unsigned int  _aircraftAddress; 
  unsigned char _aircraftIDType;
  unsigned char _dapSource;
  unsigned short _modeSAltitude;
  unsigned char _capabilityReport;
  unsigned char _paddingA;
  unsigned short _paddingB;
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
