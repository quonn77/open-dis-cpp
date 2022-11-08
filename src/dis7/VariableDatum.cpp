#include <dis7/VariableDatum.h>

#include <algorithm>
#include <cmath>

using namespace DIS;

VariableDatum::VariableDatum()
    : _variableDatumID(0),
      _variableDatumLength(0)
//   _variableDatumBits(0),
{}

VariableDatum::~VariableDatum() {}

unsigned int VariableDatum::getVariableDatumID() const {
  return _variableDatumID;
}

void VariableDatum::setVariableDatumID(unsigned int pX) {
  _variableDatumID = pX;
}

unsigned int VariableDatum::getVariableDatumLength() const {
  return _variableDatumLength;
}

void VariableDatum::setVariableDatumLength(unsigned int pX) {
  _variableDatumLength = pX;
}

std::vector<EightByteChunk>& VariableDatum::getVariableDatums() {
  return _variableDatums;
}

const std::vector<EightByteChunk>& VariableDatum::getVariableDatums() const
{
    return _variableDatums;
}

template <typename T>
void VariableDatum::swapArray(T* array, uint16_t size) {
  int temp = 0;
  int i = 0;         // pointing 1st element of the array
  int j = size - 1;  // pointing last element of the array

  while (i < j) {
    // swap
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;

    // Update i and j
    i++;
    j--;
  }
}

void VariableDatum::shiftLeft(unsigned char* array, uint16_t len,
                              uint32_t shift) {
  uint32_t i = 0;

  // compute how many bytes eventually we have to shift
  // if we have to shift 10 bit we will lose the first byte
  uint8_t start = shift / 8;

  // Compute how many bytes we have to process
  uint8_t remainingBytes = len - start;

  // compute how many bits we have to shift on the first byte (E.g. 10 we have
  // to shift 2 bit on the first valid byte)
  uint8_t rest = shift % 8;
  uint8_t next = 0;

  if (start >= len) {
    for (i = 0; i < len; i++) {
      array[i] = 0;
    }
    return;
  }

  for (i = 0; i < len; i++) {
    if ((i + 1) < len) {
      next = array[i + start + 1] << (8 - rest);
      next &= 0xFF;
    } else {
      next = 0;
    }
    uint8_t value = next | (array[i + start] >> rest);
    array[i] = value;
    if (i >= remainingBytes) {
      array[i] = 0;
    }
  }
}

void VariableDatum::shiftRight(unsigned char* array, uint16_t len,
                               uint32_t shift) {
  for (int i = 0; i < len; i++) {
    unsigned char val = array[i];
    unsigned char high = (val & 0xF0) >> 4;
    unsigned char low = (val & 0x0F) << 4;
    array[i] = high | low;
  }
  swapArray(array, len);
  shiftLeft(array, len, shift);
  swapArray(array, len);
  for (int i = 0; i < len; i++) {
    unsigned char val = array[i];
    unsigned char high = (val & 0xF0) >> 4;
    unsigned char low = (val & 0x0F) << 4;
    array[i] = low | high;
  }
}

unsigned char* VariableDatum::getPayLoad(bool shiftRightOption) {
  // we have to take the ceiling integer (20 bits shall be transmitted using 3
  // bytes)
  unsigned int bytesLength =
      static_cast<unsigned int>(ceil(_variableDatumLength / 8.0));

  // count how many chunks we have to iterate. If we have 3 bytes of data we
  // have to process at least a chunk, so we use ceil
  unsigned int chunksLength =
      static_cast<unsigned int>(ceil(bytesLength / 8.0));

  // We have to send at least 64 bit of data
  unsigned int paddingBits = getPaddingBits();

  /**
   * allocate the char* bytebuffer
   */
  unsigned char* bytesBuffer = new unsigned char[bytesLength];
  int totalBytesProcessed = 0;

  // Copy from the ByteChunk to the array of bytes to be returned
  for (int i = 0; i < chunksLength; i++) {
    DIS::EightByteChunk chunk = _variableDatums[i];
    char* chunkData = chunk.getOtherParameters();
    for (int j = 0; j < 8 && totalBytesProcessed <= bytesLength; j++) {
      bytesBuffer[totalBytesProcessed++] = chunkData[j];
    }
  }

  // Now it's time to shift right data according to padding and if requested
  if (shiftRightOption) {
    shiftRight(bytesBuffer, bytesLength, paddingBits);
  }
  return bytesBuffer;
}

void VariableDatum::setPayLoad(unsigned char* data, int howManyBytes) {
  // count how many chunks we have to iterate. If we have 3 bytes of data we
  // have to process at least a chunk, so we use ceil
  unsigned int chunksLength =
      static_cast<unsigned int>(ceil(howManyBytes / 8.0));
  int totalBytesProcessed = 0;

  for (int i = 0; i < chunksLength; i++) {
    DIS::EightByteChunk chunk = _variableDatums[i];
    char* charData = new char[8];
    for (int k = 0; k < 8; k++) {
      charData[k] = 0x0;
    }
    for (int j = 0; j < 8 && totalBytesProcessed <= howManyBytes; j++) {
      charData[j] = data[totalBytesProcessed++];
    }
    // charData is already null initialized so data is already 64bit padded
    chunk.setOtherParameters(charData);
  }
}

unsigned int VariableDatum::getPaddingBits() const {
  return 64 - (_variableDatumLength % 64);
}

void VariableDatum::marshal(DataStream& dataStream) const {
  dataStream << _variableDatumID;

  // Padding bits are not included in the Variable Datum Length.
  // IEEE Std 1278.1-2012 page 345
  // So we cannot assume that all the EightByteChunk is all variable datum data
  // We have to rely on what the client of the API will use but at the same time
  // we have to grant that the _variableDatumLength could not be greater than
  // the available EightByteChunk
  dataStream << static_cast<unsigned int>(std::min(
      _variableDatumLength, (unsigned int)_variableDatums.size() * 64));

  for (size_t idx = 0; idx < _variableDatums.size(); idx++) {
    EightByteChunk x = _variableDatums[idx];
    x.marshal(dataStream);
  }
}

void VariableDatum::unmarshal(DataStream& dataStream) {
  dataStream >> _variableDatumID;
  dataStream >> _variableDatumLength;
  unsigned int numberOfChunks =
      static_cast<unsigned int>(std::ceil(_variableDatumLength / 64.0));

  //(_variableDatumLength / 64) + ((_variableDatumLength % 64) > 0);

  _variableDatums.clear();
  for (size_t idx = 0; idx < numberOfChunks; idx++) {
    EightByteChunk x;
    x.unmarshal(dataStream);
    _variableDatums.push_back(x);
  }
}

bool VariableDatum::operator==(const VariableDatum& rhs) const {
  bool ivarsEqual = true;

  if (!(_variableDatumID == rhs._variableDatumID)) ivarsEqual = false;
  if (!(_variableDatumLength == rhs._variableDatumLength)) ivarsEqual = false;
  for (int i = 0; i < _variableDatums.size(); i++) {
    if (!(_variableDatums[i] == rhs._variableDatums[i])) ivarsEqual = false;
  }

  return ivarsEqual;
}

int VariableDatum::getMarshalledSize() const {
  int marshalSize = 0;

  marshalSize = marshalSize + 4;  // _variableDatumID
  marshalSize = marshalSize + 4;  // _variableDatumLength
  //_variableDatumBits contains also the padding (it has been modelled to be 64
  // bit aligned)
  marshalSize = marshalSize + _variableDatums.size() * 8;  // _variableDatumBits
  return marshalSize;
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
