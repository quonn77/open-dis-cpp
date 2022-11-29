#include <dis7/Mode5TransponderBasicData.h>

using namespace DIS;

Mode5TransponderBasicData::Mode5TransponderBasicData()
    : _m5Status(0),
      _pin(0),
      _m5MessageFormatPresent(0),
      _enhancedMode1(0),
      _nationalOrigin(0),
      _supplementalData(0),
      _navigationSource(0),
      _figureOfMerit(0),
      _padding(0) {}

Mode5TransponderBasicData::~Mode5TransponderBasicData() {}

bool Mode5TransponderBasicData::operator==(
    const Mode5TransponderBasicData& rhs) const {
  bool ivarsEqual = true;
  if (!(_m5MessageFormatPresent == rhs._m5MessageFormatPresent))
    ivarsEqual = false;
  if (!(_m5Status == rhs._m5Status)) ivarsEqual = false;
  if (!(_pin == rhs._pin)) ivarsEqual = false;
  if (!(_nationalOrigin == rhs._nationalOrigin)) ivarsEqual = false;
  if (!(_enhancedMode1 == rhs._enhancedMode1)) ivarsEqual = false;
  if (!(_supplementalData == rhs._supplementalData)) ivarsEqual = false;
  if (!(_navigationSource == rhs._navigationSource)) ivarsEqual = false;
  if (!(_figureOfMerit == rhs._figureOfMerit)) ivarsEqual = false;
  if (!(_padding == rhs._padding)) ivarsEqual = false;
  return ivarsEqual;
}

int Mode5TransponderBasicData::getMarshalledSize() const {
  int marshalSize = 0;

  marshalSize += 2;  // mode 5 status
  marshalSize += 2;  // pin
  marshalSize += 4;  // _m5MessageFormatPresent 32 bit record
  marshalSize += 2;  // enancheMode1 16 bit
  marshalSize += 2;  // _nationalOrigin
  marshalSize += 1;  // _supplementalData
  marshalSize += 1;  // _navigationSource
  marshalSize += 1;  // _fom
  marshalSize += 1;  // padding
  return marshalSize;
}

void Mode5TransponderBasicData::marshal(DataStream& dataStream) const {
  dataStream << _m5Status;
  dataStream << _pin;
  dataStream << _m5MessageFormatPresent;
  dataStream << _enhancedMode1;
  dataStream << _nationalOrigin;
  dataStream << _supplementalData;
  dataStream << _navigationSource;
  dataStream << _figureOfMerit;
  dataStream << _padding;
}

void Mode5TransponderBasicData::unmarshal(DataStream& dataStream) {
  dataStream >> _m5Status;
  dataStream >> _pin;
  dataStream >> _m5MessageFormatPresent;
  dataStream >> _enhancedMode1;
  dataStream >> _nationalOrigin;
  dataStream >> _supplementalData;
  dataStream >> _navigationSource;
  dataStream >> _figureOfMerit;
  dataStream >> _padding;
}

unsigned short Mode5TransponderBasicData::getMode5Status() { return _m5Status; }
void Mode5TransponderBasicData::setMode5Status(unsigned short status) {
  this->_m5Status = status;
}

unsigned short Mode5TransponderBasicData::getPIN() { return _pin; }
void Mode5TransponderBasicData::setPIN(unsigned short pin) { this->_pin = pin; }

unsigned int Mode5TransponderBasicData::getM5MessageFormatPresent() {
  return _m5MessageFormatPresent;
}

void Mode5TransponderBasicData::setM5MessageFormatPresent(unsigned int format) {
  this->_m5MessageFormatPresent = format;
}

unsigned short Mode5TransponderBasicData::getEnhancedMode1() {
  return this->_enhancedMode1;
}
void Mode5TransponderBasicData::setEnhancedMode1(unsigned short enhancedMode1) {
  this->_enhancedMode1 = enhancedMode1;
}

unsigned short Mode5TransponderBasicData::getNationalOrigin() {
  return this->_nationalOrigin;
}
void Mode5TransponderBasicData::setNationalOrigin(
    unsigned short nationalOrigin) {
  this->_nationalOrigin = nationalOrigin;
}
unsigned char Mode5TransponderBasicData::getSupplementalData() {
  return this->_supplementalData;
}
void Mode5TransponderBasicData::setSupplementalData(
    unsigned char supplementalData) {
  this->_supplementalData = supplementalData;
}

unsigned char Mode5TransponderBasicData::getNavigationSource() {
  return this->_navigationSource;
}
void Mode5TransponderBasicData::setNavigationSource(
    unsigned char navigationSource) {
  this->_navigationSource = navigationSource;
}

unsigned char Mode5TransponderBasicData::getFigureOfMerit() {
  return this->_figureOfMerit;
}
void Mode5TransponderBasicData::setFigureOfMerit(unsigned char fom) {
  this->_figureOfMerit = fom;
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
