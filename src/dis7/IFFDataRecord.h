#pragma once

#include <dis7/BeamData.h>
#include <dis7/IFFFundamentalParameterData.h>
#include <dis7/LayerHeader.h>
#include <dis7/PduSuperclass.h>
#include <dis7/SecondaryOperationalData.h>
#include <dis7/msLibMacro.h>
#include <utils/DataStream.h>

namespace DIS {

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All
// rights reserved.
//
// @author Alessio Iannone, aia
class EXPORT_MACRO IFFDataRecord {
 public:
  IFFDataRecord();
  virtual ~IFFDataRecord();
  virtual void marshal(DataStream& dataStream) const;
  virtual void unmarshal(DataStream& dataStream);
  virtual int getMarshalledSize() const;

  unsigned int getRecordType();
  void setRecordType(unsigned int recordType);

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
  unsigned short getRecordLength();

  unsigned short getRecordLength() const;

  /**
   * @brief Retrieve the length of the payload inclusive of the padding bytes
   *
   * We cannot derive the length of the specific record fields without
   * inspecting the recordType enum, so we will consider this as the length
   * inclusive of the padding
   *
   * @return unsigned short - the lenght of the record specific fields in bytes
   *                          inclusive of the padding
   */
  unsigned short getPayloadLength();

  unsigned short getPayloadLength() const;

  /**
   * @brief Get the pointer to the payload
   *
   * Please note that if you are sending the payload this,
   * according on how you use it, could contain or not the padding
   *
   * @return char*
   */
  char* getPayload();
  /**
   * @brief Copy the specific record fields to the out parameter
   *
   * This will copy the specific record fields to the out parameter
   * including also eventually any padding bytes.
   * We will not examine the whole list of record as specified
   * by the UID 66
   *
   * @param outResult the otuput pointer where we will copy data
   * @param length the length of the out parameter char*, this ideally
   *               should be the same as getPayloadLength (or at least <=,
   *               we will check this!!!)
   * @return 1 on success, !=1 otherwise
   */
  int toPayload(char* outResult, int length);
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
  void setPayload(char* payLoad, int length);

  virtual bool operator==(const IFFDataRecord& rhs) const;
 protected:
  /// UID 66
  unsigned int _recordType;

  /// 16 bit unsigned integer
  /// it start as a minimum of 6 bytes (4 for the type and 2 for the
  /// length itself and remaining bytes for the remaining fields
  /// that are Kn octects for the Record Specific fields
  /// and Pn octects for the padding to the 32 bit boundary
  /// The total size of the record is (6 + KN + PN)
  /// and so we can desume that this shall be at least 8 bytes long
  unsigned short _recordLength;

  /// we cannot derive the real payLoad size, indeed this will include the
  /// padding. So this will be _recordLength - 6 bytes (so we are removing)
  /// the length of the recordType and of the the recordLength field
  char* _payLoad;
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
