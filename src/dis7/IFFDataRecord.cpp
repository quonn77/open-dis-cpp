#include <dis7/IFFDataRecord.h>

using namespace DIS;

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All
// rights reserved.
//
// @author Alessio Iannone, aia

IFFDataRecord::IFFDataRecord()
    : _recordType(0), _recordLength(0), _payLoad(nullptr) {}
IFFDataRecord::~IFFDataRecord() { _payLoad = nullptr; }
void IFFDataRecord::marshal(DataStream& dataStream) const {
  dataStream << _recordType;
  dataStream << _recordLength;
  for (int i = 0; i < getPayloadLength(); i++) {
    dataStream << _payLoad[i];
  }
}
void IFFDataRecord::unmarshal(DataStream& dataStream) {
  dataStream >> _recordType;
  dataStream >> _recordLength;
  int payLoadLength = getPayloadLength();
  _payLoad = new char[payLoadLength];
  for (int i = 0; i < payLoadLength; i++) {
    dataStream >> _payLoad[i];
  }
}
int IFFDataRecord::getMarshalledSize() const {
  return static_cast<int>(getRecordLength());
}

unsigned int IFFDataRecord::getRecordType() { return this->_recordType; }
void IFFDataRecord::setRecordType(unsigned int recordType) {
  this->_recordType = recordType;
}

/**
 * @brief Retrieve the length of the whole record.
 *
 * The length of the whole record is (6+Kn+Pn)
 * <br>
 * The specification is not clear about how to identify
 * the length of the Record Specific Fields, apart
 * from identifying it using the record type as defined in
 * Variable Record Types [UID 66] of the SISO-REF-010-2016
 * at page 553 of 600
 *
 * @return unsigned short
 */
unsigned short IFFDataRecord::getRecordLength() { return _recordLength; }

unsigned short IFFDataRecord::getRecordLength() const { return _recordLength; }

unsigned short IFFDataRecord::getPayloadLength() {
  return getRecordLength() - 6;
}

unsigned short IFFDataRecord::getPayloadLength() const {
  return getRecordLength() - 6;
}

char* IFFDataRecord::getPayload() { return _payLoad; }
/**
 * @brief Copy the specific record fields to the out parameter
 *
 * This will copy the specific record fields to the out parameter
 * including also eventually any padding bytes.
 * We will not examine the whole list of record as specified
 * by the UID 66.
 *
 * <b>Note</b>
 * Note this will copy on the target pointer char by char
 *
 * @param outResult the otuput pointer where we will copy data
 * @param length the length of the out parameter char*, this ideally
 *               should be the same as getPayloadLength (or at least <=,
 *               we will check this!!!)
 * @return 1 on success, !=1 otherwise
 */
int IFFDataRecord::toPayload(char* outResult, int length) {
  if (length > getPayloadLength()) {
    return -1;
  }
  for (int i = 0; i < length; i++) {
    outResult[i] = _payLoad[i];
  }
  return 1;
}
/**
 * @brief Set the Payload object
 * Please note that we will send on the stream also padding bytes
 * if needed, according to the specification to adhere to the 32 bit
 * boundaries.<br>
 * So if we send a payload of 4 bytes,
 * the length shall be a multiple of 4 but 6 + 4 will be 10 so we
 * will send 2 extra padding bytes that will be taken into account
 * in the length
 * @param payLoad the char* of bytes to send
 * @param length the length in bytes of this char* (here you
 *               have to think only to the record specific fields).
 *               Padding is added by the library
 */
void IFFDataRecord::setPayload(char* payLoad, int length) {
  _recordLength = (length + 6);
  if (_recordLength % 4 != 0) {
    _recordLength = _recordLength + 4 - (_recordLength % 4);
  }
  this->_payLoad = payLoad;
}

bool IFFDataRecord::operator==(const IFFDataRecord& rhS) const {
  if (this->_recordLength != rhS._recordLength) {
    return false;
  }
  if (this->_recordType != rhS._recordType) {
    return false;
  }
  int payloadLength = getPayloadLength();
  for (int i = 0; i < payloadLength; i++) {
    if (_payLoad[i] != rhS._payLoad[i]) {
      return false;
    }
  }
  return true;
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
