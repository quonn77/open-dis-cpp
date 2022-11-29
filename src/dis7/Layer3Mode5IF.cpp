#include <dis7/Layer3Mode5IF.h>
using namespace DIS;

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All
// rights reserved.
//
// @see Table 169—Layer 3 Mode 5 Interrogator Format page 419 of IEEE Std 1278.1
//
// @author Alessio Iannone, aia

Layer3Mode5IF::Layer3Mode5IF() {}
Layer3Mode5IF::~Layer3Mode5IF() {}
void Layer3Mode5IF::marshal(DataStream& dataStream) const {
  _layerHeader.marshal(dataStream);
  _reportingSimulation.marshal(dataStream);
  _m5InterrogatorBasicData.marshal(dataStream);
  dataStream << _padding;
  dataStream << static_cast<unsigned short>(_iffParameters.size());
  for (int i = 0; i < _iffParameters.size(); i++) {
    _iffParameters.at(i).marshal(dataStream);
  }
}
void Layer3Mode5IF::unmarshal(DataStream& dataStream) {
  _layerHeader.unmarshal(dataStream);
  _reportingSimulation.unmarshal(dataStream);
  _m5InterrogatorBasicData.unmarshal(dataStream);
  dataStream >> _padding;
  dataStream >> _numberOfIFFDataRecords;
  _iffParameters.clear();
  for (int i = 0; i < _numberOfIFFDataRecords; i++) {
    IFFDataRecord dataRecord;
    dataRecord.unmarshal(dataStream);
    _iffParameters.push_back(dataRecord);
  }
}
int Layer3Mode5IF::getMarshalledSize() const {
  int size = 0;
  size += _layerHeader.getMarshalledSize();
  size += _reportingSimulation.getMarshalledSize();
  size += _m5InterrogatorBasicData.getMarshalledSize();
  size += 2;  // padding 16 bit
  size += 2;  // number of iff records;
  for (int i = 0; i < _iffParameters.size(); i++) {
    size += _iffParameters.at(i).getMarshalledSize();
  }
  return size;
}

LayerHeader& Layer3Mode5IF::getLayerHeader() { return _layerHeader; }
const LayerHeader& Layer3Mode5IF::getLayerHeader() const {
  return _layerHeader;
}
void Layer3Mode5IF::setLayerHeader(const LayerHeader& pX) {
  this->_layerHeader = pX;
}

SimulationAddress& Layer3Mode5IF::getReportingSimulation() {
  return _reportingSimulation;
}
const SimulationAddress& Layer3Mode5IF::getReportingSimulation() const {
  return _reportingSimulation;
}
void Layer3Mode5IF::setReportingSimulation(const SimulationAddress& pX) {
  this->_reportingSimulation = pX;
}

Mode5InterrogatorBasicData& Layer3Mode5IF::getMode5InterrogatorBasicData() {
  return _m5InterrogatorBasicData;
}
const Mode5InterrogatorBasicData& Layer3Mode5IF::getMode5InterrogatorBasicData()
    const {
  return _m5InterrogatorBasicData;
}
void Layer3Mode5IF::setMode5InterrogatorBasicData(
    const Mode5InterrogatorBasicData& pX) {
  this->_m5InterrogatorBasicData = pX;
}

unsigned short Layer3Mode5IF::getNumberOfIffRecords() {
  return _iffParameters.size();
}
const unsigned short Layer3Mode5IF::getNumberOfIffRecords() const {
  return _iffParameters.size();
}

std::vector<IFFDataRecord>& Layer3Mode5IF::getIFFParameters() {
  return _iffParameters;
}
const std::vector<IFFDataRecord>& Layer3Mode5IF::getIFFParameters() const {
  return _iffParameters;
}
void Layer3Mode5IF::setIFFParameters(const std::vector<IFFDataRecord>& pX) {
  _iffParameters = pX;
}

bool Layer3Mode5IF::operator==(const Layer3Mode5IF& rhS) const {

  if (!(this->_layerHeader == rhS._layerHeader)) {
    return false;
  }
  if (!(this->_m5InterrogatorBasicData == rhS._m5InterrogatorBasicData)) {
    return false;
  }
  if (!(this->_reportingSimulation == rhS._reportingSimulation)) {
    return false;
  }
  if (_iffParameters.size() != rhS._iffParameters.size()) {
    return false;
  }
  for (int i = 0; i < _iffParameters.size(); i++) {
    if (!(this->_iffParameters.at(i) == rhS._iffParameters.at(i))) {
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
