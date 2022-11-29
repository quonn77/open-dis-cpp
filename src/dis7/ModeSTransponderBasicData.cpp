#include <dis7/ModeSTransponderBasicData.h>

using namespace DIS;

ModeSTransponderBasicData::ModeSTransponderBasicData()
    : _modeSTransponderStatus(0),
      _modeSLevelPresent(0),
      _aircraftPresentDomain(0),
      _aircraftIdentification(0),
      _aircraftAddress(0),
      _aircraftIDType(0),
      _dapSource(0),
      _modeSAltitude(0),
      _capabilityReport(0),
      _paddingA(0),
      _paddingB(0) {}
ModeSTransponderBasicData::~ModeSTransponderBasicData() {}

bool ModeSTransponderBasicData::operator==(
    const ModeSTransponderBasicData& rhs) const {
  bool ivarsEqual = true;
  if (!(_modeSTransponderStatus == rhs._modeSTransponderStatus))
    ivarsEqual = false;
  if (!(_modeSLevelPresent == rhs._modeSLevelPresent)) ivarsEqual = false;
  if (!(_aircraftPresentDomain == rhs._aircraftPresentDomain))
    ivarsEqual = false;
  if (!(_aircraftIdentification == rhs._aircraftIdentification))
    ivarsEqual = false;
  if (!(_aircraftAddress == rhs._aircraftAddress)) ivarsEqual = false;
  if (!(_aircraftIDType == rhs._aircraftIDType)) ivarsEqual = false;
  if (!(_dapSource == rhs._dapSource)) ivarsEqual = false;
  if (!(_modeSAltitude == rhs._modeSAltitude)) ivarsEqual = false;
  if (!(_capabilityReport == rhs._capabilityReport)) ivarsEqual = false;
  return ivarsEqual;
}

int ModeSTransponderBasicData::getMarshalledSize() const {
  int marshalSize = 0;

  marshalSize = marshalSize + 2;  // _modeSTransponderStatus
  marshalSize = marshalSize + 1;  // mode s Level present 8 bit
  marshalSize = marshalSize + 1;  // aircraft present domain 8 bit
  marshalSize = marshalSize + 8;  // aircraft identification domain 64 bit
  marshalSize = marshalSize + 4;  // aircraft address 32 bit
  marshalSize = marshalSize + 1;  // aircraft id type 8 bit
  marshalSize = marshalSize + 1;  // dap source 8 bit
  marshalSize = marshalSize + 2;  // mode s altitude 16 bit
  marshalSize = marshalSize + 1;  // capability report 8 bit
  marshalSize = marshalSize + 1;  // padding 8 bit
  marshalSize = marshalSize + 2;  // padding 16 bit
  return marshalSize;
}

void ModeSTransponderBasicData::marshal(DataStream& dataStream) const {
  dataStream << _modeSTransponderStatus;
  dataStream << _modeSLevelPresent;
  dataStream << _aircraftPresentDomain;
  dataStream << _aircraftIdentification;
  dataStream << _aircraftAddress;
  dataStream << _aircraftIDType;
  dataStream << _dapSource;
  dataStream << _modeSAltitude;
  dataStream << _capabilityReport;
  dataStream << _paddingA;
  dataStream << _paddingB;
}

void ModeSTransponderBasicData::unmarshal(DataStream& dataStream) {
  dataStream >> _modeSTransponderStatus;
  dataStream >> _modeSLevelPresent;
  dataStream >> _aircraftPresentDomain;
  dataStream >> _aircraftIdentification;
  dataStream >> _aircraftAddress;
  dataStream >> _aircraftIDType;
  dataStream >> _dapSource;
  dataStream >> _modeSAltitude;
  dataStream >> _capabilityReport;
  dataStream >> _paddingA;
  dataStream >> _paddingB;
}

unsigned char ModeSTransponderBasicData::getModeSTransponderStatus() {
  return _modeSTransponderStatus;
}
void ModeSTransponderBasicData::setModeSTransponderStatus(
    unsigned char status) {
  this->_modeSTransponderStatus = status;
}

unsigned char ModeSTransponderBasicData::getModeSLevelPresent() {
  return _modeSLevelPresent;
}
void ModeSTransponderBasicData::setModeSLevelPresent(
    unsigned char levelPresent) {
  this->_modeSLevelPresent = levelPresent;
}

unsigned char ModeSTransponderBasicData::getAircraftPresentDomain() {
  return _aircraftPresentDomain;
}

void ModeSTransponderBasicData::setAirCraftPresentDomain(
    unsigned char aircraftPresentDomain) {
  this->_aircraftPresentDomain = aircraftPresentDomain;
}

unsigned long long ModeSTransponderBasicData::getAircraftIdentification() {
  return _aircraftIdentification;
}

void ModeSTransponderBasicData::setAircraftIdentification(
    unsigned long long identification) {
  this->_aircraftIdentification = identification;
}

unsigned int ModeSTransponderBasicData::getAircraftAddress() {
  return _aircraftAddress;
}

void ModeSTransponderBasicData::setAircraftAddress(unsigned int address) {
  this->_aircraftAddress = address;
}

unsigned char ModeSTransponderBasicData::getAircraftIDType() {
  return this->_aircraftIDType;
}

void ModeSTransponderBasicData::setAircraftIDType(unsigned char type) {
  this->_aircraftIDType = type;
}

unsigned char ModeSTransponderBasicData::getDAPSource() {
  return this->_dapSource;
}

void ModeSTransponderBasicData::setDAPSource(unsigned char source) {
  this->_dapSource = source;
}

unsigned short ModeSTransponderBasicData::getModeSAltitude(){
  return this->_modeSAltitude;
}

void ModeSTransponderBasicData::setModeSAltitude(unsigned short mSAltitude){
  this->_modeSAltitude = mSAltitude;
}

unsigned char ModeSTransponderBasicData::getCapabilityReport(){
  return this->_capabilityReport;
}

void ModeSTransponderBasicData::setCapabilityReport(unsigned char capabilityReport){
  this->_capabilityReport = capabilityReport;
}

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