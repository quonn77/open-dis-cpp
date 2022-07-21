#pragma once

#include <dis7/EightByteChunk.h>
#include <dis7/msLibMacro.h>
#include <utils/DataStream.h>
#include <stdint.h>
#include <vector>

namespace DIS {
// the variable datum type, the datum length, and the value for that variable
// datum type. NOT COMPLETE. Section 6.2.92

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All
// rights reserved.
//
// @author DMcG, jkg

class EXPORT_MACRO VariableDatum {
 protected:
  /** Type of variable datum to be transmitted. 32 bit enumeration defined in
   * EBV */
  unsigned int _variableDatumID;

  /** Length, in bits, of the variable datum. */
  unsigned int _variableDatumLength;

  /** Variable datum. This can be any number of bits long, depending on the
   * datum. */
  //   unsigned int _variableDatumBits;

  /** padding to put the record on a 64 bit boundary */
  // unsigned int _padding;

  // Variable Data
  std::vector<EightByteChunk> _variableDatums;

 public:
  VariableDatum();
  virtual ~VariableDatum();

  virtual void marshal(DataStream& dataStream) const;
  virtual void unmarshal(DataStream& dataStream);

  unsigned int getVariableDatumID() const;
  void setVariableDatumID(unsigned int pX);

  unsigned int getVariableDatumLength() const;
  void setVariableDatumLength(unsigned int pX);

  std::vector<EightByteChunk>& getVariableDatums();

  /**
   * @brief Retrieve only the array of bytes relative to the payload of the
   * Variable Datum
   *
   * Assuming to have, for example, a variable datum length of 16 bits even if
   * we have to send at least 64 bit of data (8 bytes) we will return byte array
   * of 2 bytes
   *
   * if we have a datum length of 20 bits we will return 3 bytes where we have
   * already masked the invalid bit something like (data >> 4) & 0xFFFFF.
   *
   * Use #getVariableDatumLength in order to know how many bits have been used
   * for the payload
   *
   * An please remember that if you have in memory a data like (N is 4 bit
   * group)
   *
   *       N-4  N-3  N-2  N-1  N
   * [ ... 0001 0000 1100 0011 0000 ]
   *
   * Where the last 4 bit (0000) have been used as padding we will return
   *
   *       N-3  N-2   N-1   N
   * [ ... 0001 0000 1100 0011 ]
   *
   * We have so moved N-1 into the N position
   * @param shiftRightOption (by default true) to perform the shifting as
   * described above
   * @return char* the array of data already shifted if requested
   */
  unsigned char* getPayLoad(bool shiftRightOption = true);

  /**
   * @brief Set the Pay Load
   *
   * @param data the payload
   * @param howManyBytes the dimension of the data array (the payload). Please
   * note that this is not the same as #setVariableDatumLength, indeed they both
   * coincide only if it is byte aligned (varibaleDatumLength could be 12 bit)
   * So here we don't set the variable datum length using this value
   */
  void setPayLoad(unsigned char* data, int howManyBytes);

  /**
   * @brief Retrieve how many bit have been used for padding
   *
   * @return unsigned int
   */
  unsigned int getPaddingBits() const;
  // void setPadding(unsigned int pX);

  virtual int getMarshalledSize() const;

  bool operator==(const VariableDatum& rhs) const;

 private:
  /**
   * @brief Shift an array right
   * @param array The array to shift
   * @param len The number of array elements.
   * @param shift The number of bits to shift
   */
  void shiftRight(unsigned char* array, uint16_t len, uint32_t shift);

  /**
   * @brief Shift an array left of the given bits
   *
   * @param array
   * @param len
   * @param shift
   */
  void shiftLeft(unsigned char* array, uint16_t len, uint32_t shift);

  /**
   * @brief
   *
   * @tparam T
   * @param array
   * @param size
   */
  template <typename T>
  void swapArray(T* array, uint16_t size);
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
