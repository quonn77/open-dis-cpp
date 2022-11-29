#pragma once

#include <dis7/IFFDataRecord.h>
#include <dis7/IPDU.h>
#include <dis7/LayerHeader.h>
#include <dis7/ModeSInterrogatorBasicData.h>
#include <dis7/PduSuperclass.h>
#include <dis7/SimulationAddress.h>
#include <dis7/msLibMacro.h>
#include <utils/DataStream.h>

namespace DIS {

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All
// rights reserved.
//
// @see Table 169—Layer 4 Mode S Interrogator Format page 404 of IEEE Std 1278.1
//
// @author Alessio Iannone, aia
class EXPORT_MACRO Layer4ModeSIF : public IPDU {
 public:
  Layer4ModeSIF();
  virtual ~Layer4ModeSIF();
  virtual void marshal(DataStream& dataStream) const;
  virtual void unmarshal(DataStream& dataStream);
  virtual int getMarshalledSize() const;

  LayerHeader& getLayerHeader();
  const LayerHeader& getLayerHeader() const;
  void setLayerHeader(const LayerHeader& pX);

  SimulationAddress& getReportingSimulation();
  const SimulationAddress& getReportingSimulation() const;
  void setReportingSimulation(const SimulationAddress& pX);

  ModeSInterrogatorBasicData& getModeSInterrogatorBasicData();
  const ModeSInterrogatorBasicData& getModeSInterrogatorBasicData() const;
  void setModeSInterrogatorBasicData(const ModeSInterrogatorBasicData& pX);

  unsigned short getNumberOfIffRecords();
  const unsigned short getNumberOfIffRecords() const;

  std::vector<IFFDataRecord>& getIFFParameters();
  const std::vector<IFFDataRecord>& getIFFParameters() const;
  void setIFFParameters(const std::vector<IFFDataRecord>& pX);
  virtual bool operator==(const Layer4ModeSIF& rhs) const;

 protected:
  LayerHeader _layerHeader;
  SimulationAddress _reportingSimulation;
  ModeSInterrogatorBasicData _mSInterrogatorBasicData;
  unsigned short _padding;
  unsigned short _numberOfIFFDataRecords;
  std::vector<IFFDataRecord> _iffParameters;
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
