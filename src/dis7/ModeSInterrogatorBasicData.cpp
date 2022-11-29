#include <dis7/ModeSInterrogatorBasicData.h>

using namespace DIS;

ModeSInterrogatorBasicData::ModeSInterrogatorBasicData()
    : _modeSInterrogatorStatus(0),
      _modeSLevelPresent(0),
      _paddingA(0),
      _paddingB(0) {
  for (size_t i = 0; i < 5; i++) {
    _padding[i] = 0;
  }
}
ModeSInterrogatorBasicData::~ModeSInterrogatorBasicData() {}

bool ModeSInterrogatorBasicData::operator==(
    const ModeSInterrogatorBasicData& rhs) const {
  bool ivarsEqual = true;
  if (!(_modeSInterrogatorStatus == rhs._modeSInterrogatorStatus))
    ivarsEqual = false;
  if (!(_modeSLevelPresent == rhs._modeSLevelPresent)) ivarsEqual = false;
  return ivarsEqual;
}

int ModeSInterrogatorBasicData::getMarshalledSize() const {
  int marshalSize = 0;

  marshalSize = marshalSize + 1;   // _modeSInterrogatorStatus 8 bit
  marshalSize = marshalSize + 1;   // padding 8 bit
  marshalSize = marshalSize + 1;   // _modeSLevelPresent 8 bit
  marshalSize = marshalSize + 1;   // padding 8 bit
  marshalSize = marshalSize + 20;  // padding 5 x 32 bit = 160 bit = 20 bytes
  return marshalSize;
}

void ModeSInterrogatorBasicData::marshal(DataStream& dataStream) const {
  dataStream << _modeSInterrogatorStatus;
  dataStream << _paddingA;
  dataStream << _modeSLevelPresent;
  dataStream << _paddingB;
  for (size_t i = 0; i < 5; i++) {
    dataStream << _padding[i];
  }
}

void ModeSInterrogatorBasicData::unmarshal(DataStream& dataStream) {
  dataStream >> _modeSInterrogatorStatus;
  dataStream >> _paddingA;
  dataStream >> _modeSLevelPresent;
  dataStream >> _paddingB;
  for (size_t i = 0; i < 5; i++) {
    dataStream >> _padding[i];
  }
}

unsigned char ModeSInterrogatorBasicData::getModeSInterrogatorStatus() {
  return _modeSInterrogatorStatus;
}
void ModeSInterrogatorBasicData::setModeSInterrogatorStatus(
    unsigned char status) {
  this->_modeSInterrogatorStatus = status;
}

unsigned char ModeSInterrogatorBasicData::getModeSLevelPresent() {
  return _modeSLevelPresent;
}
void ModeSInterrogatorBasicData::setModeSLevelPresent(
    unsigned char mSLevelPresent) {
  this->_modeSLevelPresent = mSLevelPresent;
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
