#pragma once

#include <dis7/IPDU.h>
#include <dis7/Layer3Mode5IF.h>
#include <dis7/Layer3Mode5TF.h>

namespace DIS {

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All
// rights reserved.
//
// @see Table 169—Layer 3 Mode 5 Interrogator Format page 419 of IEEE Std 1278.1
//
// @author Alessio Iannone, aia
enum class Layer3Type { INVALID, Layer3Mode5IF, Layer3Mode5TF };

class EXPORT_MACRO Layer3 : public IPDU {
 public:
  Layer3() = delete;
  Layer3(bool transponder);
  virtual ~Layer3();

  virtual void marshal(DataStream& dataStream) const;
  virtual void unmarshal(DataStream& dataStream);
  virtual int getMarshalledSize() const;

  Layer3Type discriminator();
  Layer3Type discriminator() const;

  /**
   * @brief Reuse this object by allocating the proper object according tot the
   * transponder parameter
   *
   * Note this method will destroy any previous object allocated
   *
   * @param transponder
   */
  void discriminator(bool transponder);

  /**
   * @brief Get the Layer3 Mode5 IF object or nullptr if this is the wrong layer
   * type
   *
   * @return Layer3Mode5IF* or nullptr if this is the wrong layer type
   */
  Layer3Mode5IF* getLayer3Mode5IF();
  Layer3Mode5IF* getLayer3Mode5IF() const;
  void setLayer3Mode5IF(Layer3Mode5IF* pX);

  /**
   * @brief Get the Layer3 Mode5 TF object, or nullptr if wrong layertype union
   *
   * @return Layer3Mode5TF* or nullptr if this is the wrong layertype
   */
  Layer3Mode5TF* getLayer3Mode5TF();
  Layer3Mode5TF* getLayer3Mode5TF() const;
  void setLayer3Mode5TF(Layer3Mode5TF* pX);

  virtual bool operator==(const IPDU& rhs) const;

 protected:
  Layer3Type _layer3Type;
  Layer3Mode5IF* _layer3Mode5IFpx;
  Layer3Mode5TF* _layer3Mode5TFpx;

 public:
  /**
   * @brief Get the Layer3 PDU object handled by this Union like class
   *  
   * @return IPDU* the concrete Layer implementation we are using
   *         You can cast to the concrete object, but it is suggested to use
   *         the convenience method #getLayer3Mode5TF or #getLayer3Mode5IF
   */
  IPDU* getLayer3PDU() const;
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
