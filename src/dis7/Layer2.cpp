#include "Layer2.h"
using namespace DIS;

Layer2::Layer2() : _layerHeader(), _beamData(), _secondaryOperationalData() {
  ;
}
Layer2::~Layer2() { _iffParameters.clear(); }

void Layer2::marshal(DataStream& dataStream) const {
  _layerHeader.marshal(dataStream);
  _beamData.marshal(dataStream);
  _secondaryOperationalData.marshal(dataStream);
  dataStream << (unsigned char)_iffParameters.size();
  for (size_t idx = 0; idx < _iffParameters.size(); idx++) {
    IFFFundamentalParameterData x = _iffParameters[idx];
    x.marshal(dataStream);
  }
}

void Layer2::unmarshal(DataStream& dataStream) {
  _layerHeader.unmarshal(dataStream);
  _beamData.unmarshal(dataStream);
  _secondaryOperationalData.unmarshal(dataStream);
  unsigned short numberOfIFFParameters =
      _secondaryOperationalData.getNumberOfIFFFundamentalParameterRecords();
  _iffParameters.clear();
  for (size_t idx = 0; idx < numberOfIFFParameters; idx++) {
    IFFFundamentalParameterData x;
    x.unmarshal(dataStream);
    _iffParameters.push_back(x);
  }
}
LayerHeader& Layer2::getLayerHeader() { return _layerHeader; }

const LayerHeader& Layer2::getLayerHeader() const { return _layerHeader; }

void Layer2::setLayerHeader(const LayerHeader& pX) { _layerHeader = pX; }

BeamData& Layer2::getBeamData() { return _beamData; }

const BeamData& Layer2::getBeamData() const { return _beamData; }

void Layer2::setBeamData(const BeamData& pX) { _beamData = pX; }

SecondaryOperationalData& Layer2::getSecondaryOperationalData() {
  return _secondaryOperationalData;
}

const SecondaryOperationalData& Layer2::getSecondaryOperationalData() const {
  return _secondaryOperationalData;
}

void Layer2::setSecondaryOperationalData(const SecondaryOperationalData& pX) {
  _secondaryOperationalData = pX;
}

std::vector<IFFFundamentalParameterData>& Layer2::getIFFParameters() {
  return _iffParameters;
}

const std::vector<IFFFundamentalParameterData>& Layer2::getIFFParameters()
    const {
  return _iffParameters;
}

void Layer2::setIFFParameters(
    const std::vector<IFFFundamentalParameterData>& pX) {
  _iffParameters = pX;
}
int Layer2::getMarshalledSize() const {
  int marshalSize = 0;

  marshalSize = marshalSize + _layerHeader.getMarshalledSize();  // _layerHeader
  marshalSize = marshalSize + _beamData.getMarshalledSize();     // _beamData
  marshalSize =
      marshalSize + _secondaryOperationalData
                        .getMarshalledSize();  // _secondaryOperationalData

  for (unsigned long long idx = 0; idx < _iffParameters.size(); idx++) {
    IFFFundamentalParameterData listElement = _iffParameters[idx];
    marshalSize = marshalSize + listElement.getMarshalledSize();
  }
}