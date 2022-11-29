#include <dis7/Mode5InterrogatorBasicData.h>

using namespace DIS;

Mode5InterrogatorBasicData::Mode5InterrogatorBasicData()
    : _m5InterrogatorStatus(0), _m5MessageFormatPresent(0) {}
Mode5InterrogatorBasicData::~Mode5InterrogatorBasicData() {}

bool Mode5InterrogatorBasicData::operator==(
    const Mode5InterrogatorBasicData& rhs) const {
  bool ivarsEqual = true;
  if (!(_m5InterrogatorStatus == rhs._m5InterrogatorStatus)) ivarsEqual = false;
  if (!(_m5MessageFormatPresent == rhs._m5MessageFormatPresent))
    ivarsEqual = false;
  if (!(_interrogatedEntityID == rhs._interrogatedEntityID)) ivarsEqual = false;
  return ivarsEqual;
}

int Mode5InterrogatorBasicData::getMarshalledSize() const {
  int marshalSize = 0;

  marshalSize = marshalSize + 1;  // _m5InterrogatorStatus
  marshalSize = marshalSize + 1;  // padding 8 bit
  marshalSize = marshalSize + 2;  // padding 16 bit
  marshalSize = marshalSize + 4;  // _m5MessageFormatPresent 32 bit record
  marshalSize = marshalSize + _interrogatedEntityID.getMarshalledSize();  // _interrogatedEntityID
  marshalSize = marshalSize + 2;  // padding 16 bit
  return marshalSize;
}

void Mode5InterrogatorBasicData::marshal(DataStream& dataStream) const {
  dataStream << _m5InterrogatorStatus;
  dataStream << _padding1;
  dataStream << _padding2;
  dataStream << _m5MessageFormatPresent;
  _interrogatedEntityID.marshal(dataStream);
  dataStream << _padding3;
}

void Mode5InterrogatorBasicData::unmarshal(DataStream& dataStream) {
  dataStream >> _m5InterrogatorStatus;
  dataStream >> _padding1;
  dataStream >> _padding2;
  dataStream >> _m5MessageFormatPresent;
  _interrogatedEntityID.unmarshal(dataStream);
  dataStream >> _padding3;
}

unsigned char Mode5InterrogatorBasicData::getM5InterrogatorStatus() {
  return _m5InterrogatorStatus;
}
void Mode5InterrogatorBasicData::setM5InterrogatorStatus(unsigned char status) {
  this->_m5InterrogatorStatus = status;
}

unsigned int Mode5InterrogatorBasicData::getM5MessageFormatPresent() {
  return _m5MessageFormatPresent;
}
void Mode5InterrogatorBasicData::setM5MessageFormatPresent(
    unsigned int m5MessageFormat) {
  this->_m5MessageFormatPresent = m5MessageFormat;
}

EntityID& Mode5InterrogatorBasicData::getInterrogatedEntityID() {
  return _interrogatedEntityID;
}

const EntityID& Mode5InterrogatorBasicData::getInterrogatedEntityID() const {
  return _interrogatedEntityID;
}

void Mode5InterrogatorBasicData::setInterrogatedEntityID(
    const EntityID& entityID) {
  this->_interrogatedEntityID = entityID;
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
