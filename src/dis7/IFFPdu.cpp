#include <dis7/IFFPdu.h>

using namespace DIS;

IFFPdu::IFFPdu()
    : DistributedEmissionsFamilyPdu(),
      _emittingEntityID(),
      _eventID(),
      _relativeAntennaLocation(),
      _numberOfIFFParameters(0),
      _systemID(),
      _systemDesignator(0),
      _systemSpecificData(0),
      _fundamentalOperationalData(),
      _layer2()
// _layerHeader(),
// _beamData(),
// _secondaryOperationalData()
{
  setPduType(28);
}

IFFPdu::~IFFPdu() {
  // _iffParameters.clear();
}

Layer2& IFFPdu::getLayer2() { return _layer2; }
const Layer2& IFFPdu::getLayer2() const { return _layer2; }
void IFFPdu::setLayer2(const Layer2& pX){
  this->_layer2 = pX;
}

EntityID& IFFPdu::getEmittingEntityID() {
  return _emittingEntityID; }

const EntityID& IFFPdu::getEmittingEntityID() const {
  return _emittingEntityID;
}

void IFFPdu::setEmittingEntityID(const EntityID& pX) {
  _emittingEntityID = pX; }

EventIdentifier& IFFPdu::getEventID() {
  return _eventID; }

const EventIdentifier& IFFPdu::getEventID() const {
  return _eventID; }

void IFFPdu::setEventID(const EventIdentifier& pX) {
  _eventID = pX; }

Vector3Float& IFFPdu::getRelativeAntennaLocation() {
  return _relativeAntennaLocation;
}

const Vector3Float& IFFPdu::getRelativeAntennaLocation() const {
  return _relativeAntennaLocation;
}

void IFFPdu::setRelativeAntennaLocation(const Vector3Float& pX) {
  _relativeAntennaLocation = pX;
}

unsigned int IFFPdu::getNumberOfIFFParameters() const {
  return _numberOfIFFParameters;
}

SystemIdentifier& IFFPdu::getSystemID() {
  return _systemID; }

const SystemIdentifier& IFFPdu::getSystemID() const {
  return _systemID; }

void IFFPdu::setSystemID(const SystemIdentifier& pX) {
  _systemID = pX; }

unsigned char IFFPdu::getSystemDesignator() const {
  return _systemDesignator; }

void IFFPdu::setSystemDesignator(unsigned char pX) {
  _systemDesignator = pX; }

unsigned char IFFPdu::getSystemSpecificData() const {
  return _systemSpecificData;
}

void IFFPdu::setSystemSpecificData(unsigned char pX) {
  _systemSpecificData = pX;
}

FundamentalOperationalData& IFFPdu::getFundamentalOperationalData() {
  return _fundamentalOperationalData;
}

const FundamentalOperationalData& IFFPdu::getFundamentalOperationalData()
    const {
  return _fundamentalOperationalData;
}

void IFFPdu::setFundamentalOperationalData(
    const FundamentalOperationalData& pX) {
  _fundamentalOperationalData = pX;
}

void IFFPdu::marshal(DataStream& dataStream) const {
  DistributedEmissionsFamilyPdu::marshal(
      dataStream);  // Marshal information in superclass first
  _emittingEntityID.marshal(dataStream);
  _eventID.marshal(dataStream);
  _relativeAntennaLocation.marshal(dataStream);
  _systemID.marshal(dataStream);
  dataStream << _systemDesignator;
  dataStream << _systemSpecificData;
  _fundamentalOperationalData.marshal(dataStream);

  // We have to marshall layer 2 only if the info is available
  if (_fundamentalOperationalData.getInformationLayers() & (0x1 << 2) == 1) {
    _layer2.marshal(dataStream);
  }
}

void IFFPdu::unmarshal(DataStream& dataStream) {
  DistributedEmissionsFamilyPdu::unmarshal(
      dataStream);  // unmarshal information in superclass first
  _emittingEntityID.unmarshal(dataStream);
  _eventID.unmarshal(dataStream);
  _relativeAntennaLocation.unmarshal(dataStream);
  _systemID.unmarshal(dataStream);
  dataStream >> _systemDesignator;
  dataStream >> _systemSpecificData;
  _fundamentalOperationalData.unmarshal(dataStream);
  // Other fields are optional we have to unmarshall only if defined inside the
  // fundamental operational data We have to check the third bit (bit in
  // position 2 starting from 0)
  if (_fundamentalOperationalData.getInformationLayers() & (0x1 << 2) == 1) {
    _layer2.unmarshal(dataStream);
  }
}

bool IFFPdu::operator==(const IFFPdu& rhs) const {
  bool ivarsEqual = true;

  ivarsEqual = DistributedEmissionsFamilyPdu::operator==(rhs);

  if (!(_emittingEntityID == rhs._emittingEntityID)) ivarsEqual = false;
  if (!(_eventID == rhs._eventID)) ivarsEqual = false;
  if (!(_relativeAntennaLocation == rhs._relativeAntennaLocation))
    ivarsEqual = false;
  if (!(_systemID == rhs._systemID)) ivarsEqual = false;
  if (!(_systemDesignator == rhs._systemDesignator)) ivarsEqual = false;
  if (!(_systemSpecificData == rhs._systemSpecificData)) ivarsEqual = false;
  if (!(_fundamentalOperationalData == rhs._fundamentalOperationalData))
    ivarsEqual = false;

  // if (!(_layerHeader == rhs._layerHeader)) ivarsEqual = false;
  // if (!(_beamData == rhs._beamData)) ivarsEqual = false;
  // if (!(_secondaryOperationalData == rhs._secondaryOperationalData))
  //   ivarsEqual = false;

  // for (size_t idx = 0; idx < _iffParameters.size(); idx++) {
  //   if (!(_iffParameters[idx] == rhs._iffParameters[idx])) ivarsEqual =
  //   false;
  // }

  return ivarsEqual;
}

int IFFPdu::getMarshalledSize() const {
  int marshalSize = 0;

  marshalSize = DistributedEmissionsFamilyPdu::getMarshalledSize();
  marshalSize =
      marshalSize + _emittingEntityID.getMarshalledSize();  // _emittingEntityID
  marshalSize = marshalSize + _eventID.getMarshalledSize();  // _eventID
  marshalSize =
      marshalSize +
      _relativeAntennaLocation.getMarshalledSize();  //_relativeAntennaLocation
  marshalSize = marshalSize + 1;                     // _numberOfIFFParameters
  marshalSize = marshalSize + _systemID.getMarshalledSize();  //_systemID
  marshalSize = marshalSize + 1;  //_systemDesignator
  marshalSize = marshalSize + 1;  //_systemSpecificData
  marshalSize =
      marshalSize + _fundamentalOperationalData
                        .getMarshalledSize();  // _fundamentalOperationalData

  // marshalSize = marshalSize + _layerHeader.getMarshalledSize();  //
  // _layerHeader marshalSize = marshalSize + _beamData.getMarshalledSize(); //
  // _beamData marshalSize =
  //     marshalSize + _secondaryOperationalData
  //                       .getMarshalledSize();  // _secondaryOperationalData

  // for (unsigned long long idx = 0; idx < _iffParameters.size(); idx++) {
  //   IFFFundamentalParameterData listElement = _iffParameters[idx];
  //   marshalSize = marshalSize + listElement.getMarshalledSize();
  // }

  return marshalSize;
}
