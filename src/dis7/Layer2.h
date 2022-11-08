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
class EXPORT_MACRO Layer2 {
 public:
  Layer2();
  virtual ~Layer2();
  virtual void marshal(DataStream& dataStream) const;
  virtual void unmarshal(DataStream& dataStream);
  virtual int getMarshalledSize() const;

  

  LayerHeader& getLayerHeader();
  const LayerHeader& getLayerHeader() const;
  void setLayerHeader(const LayerHeader& pX);

  BeamData& getBeamData();
  const BeamData& getBeamData() const;
  void setBeamData(const BeamData& pX);

  SecondaryOperationalData& getSecondaryOperationalData();
  const SecondaryOperationalData& getSecondaryOperationalData() const;
  void setSecondaryOperationalData(const SecondaryOperationalData& pX);

  std::vector<IFFFundamentalParameterData>& getIFFParameters();
  const std::vector<IFFFundamentalParameterData>& getIFFParameters() const;
  void setIFFParameters(const std::vector<IFFFundamentalParameterData>& pX);

 protected:
  LayerHeader _layerHeader;
  BeamData _beamData;
  SecondaryOperationalData _secondaryOperationalData;
  std::vector<IFFFundamentalParameterData> _iffParameters;
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
