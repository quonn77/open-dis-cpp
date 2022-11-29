#pragma once

#include <dis7/IPDU.h>
#include <dis7/Layer4ModeSIF.h>
#include <dis7/Layer4ModeSTF.h>

namespace DIS {

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All
// rights reserved.
//
// @see Table 169—Layer 3 Mode 5 Interrogator Format page 419 of IEEE Std 1278.1
//
// @author Alessio Iannone, aia
enum class Layer4Type { INVALID,Layer4ModeSIF, Layer4ModeSTF };

class EXPORT_MACRO Layer4 : public IPDU {
 public:
  Layer4() = delete;
  Layer4(bool transponder);
  virtual ~Layer4();

  virtual void marshal(DataStream& dataStream) const;
  virtual void unmarshal(DataStream& dataStream);
  virtual int getMarshalledSize() const;

  Layer4Type discriminator();
  Layer4Type discriminator() const;

  /**
   * @brief Initialize the layer4 with the proper body
   * 
   * @param transponder 
   */
  void discriminator(bool transponder);
  
  /**
   * @brief Get the Layer4 Mode S IF object or nullptr if this is the wrong layer type
   * 
   * @return Layer4ModeSIF* or nullptr if this is the wrong layer type
   */
  Layer4ModeSIF* getLayer4ModeSIF();
  Layer4ModeSIF* getLayer4ModeSIF() const;
  void setLayer4ModeSIF(Layer4ModeSIF* pX);

  /**
   * @brief Get the Layer4 ModeS TF object, or nullptr if wrong layertype union
   * 
   * @return Layer4ModeSTF* or nullptr if this is the wrong layertype
   */
  Layer4ModeSTF* getLayer4ModeSTF();
  Layer4ModeSTF* getLayer4ModeSTF() const;
  void setLayer4ModeSTF(Layer4ModeSTF* pX);
  

 protected:
  Layer4Type _layer4Type;
  Layer4ModeSIF* _layer4ModeSIFpx;
  Layer4ModeSTF* _layer4ModeSTFpx;

 public:
  /**
   * @brief Get the Layer4 PDU object handled by this Union like class
   * 
   * @return IPDU* the concrete Layer implementation we are using
   */
  IPDU* getLayer4PDU() const;
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
