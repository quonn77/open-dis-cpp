#include <dis7/IFFPdu.h>

#include <iostream>
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
      _layer2(),
      _layer3(nullptr),
      _layer4(nullptr) {
  setPduType(28);
}

IFFPdu::~IFFPdu() {
  // _iffParameters.clear();
}

Layer2& IFFPdu::getLayer2() { return _layer2; }
const Layer2& IFFPdu::getLayer2() const { return _layer2; }
void IFFPdu::setLayer2(const Layer2& pX) { this->_layer2 = pX; }

Layer3* IFFPdu::getLayer3() { return _layer3; }
Layer3* IFFPdu::getLayer3() const { return _layer3; }
void IFFPdu::setLayer3(Layer3* pX) { this->_layer3 = pX; }

Layer4* IFFPdu::getLayer4() { return _layer4; }
Layer4* IFFPdu::getLayer4() const { return _layer4; }
void IFFPdu::setLayer4(Layer4* pX) { this->_layer4 = pX; }

EntityID& IFFPdu::getEmittingEntityID() { return _emittingEntityID; }

const EntityID& IFFPdu::getEmittingEntityID() const {
  return _emittingEntityID;
}

void IFFPdu::setEmittingEntityID(const EntityID& pX) { _emittingEntityID = pX; }

EventIdentifier& IFFPdu::getEventID() { return _eventID; }

const EventIdentifier& IFFPdu::getEventID() const { return _eventID; }

void IFFPdu::setEventID(const EventIdentifier& pX) { _eventID = pX; }

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

SystemIdentifier& IFFPdu::getSystemID() { return _systemID; }

const SystemIdentifier& IFFPdu::getSystemID() const { return _systemID; }

void IFFPdu::setSystemID(const SystemIdentifier& pX) { _systemID = pX; }

unsigned char IFFPdu::getSystemDesignator() const { return _systemDesignator; }

void IFFPdu::setSystemDesignator(unsigned char pX) { _systemDesignator = pX; }

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
  unsigned short systemType = getSystemID().getSystemType();
  bool transponder = getSystemID().isTransponder();
  // We have to marshall layer 2 only if the info is available
  if (_fundamentalOperationalData.isInformationLayerPresent(2)) {
    _layer2.marshal(dataStream);
  }

  if (_fundamentalOperationalData.isInformationLayerPresent(3)) {
    if (_layer3 != nullptr) {
      _layer3->discriminator(transponder);
      _layer3->marshal(dataStream);
    } else {
      std::string message(
          "Layer3 has been declared as present, but has not been set!!");
      std::cerr << message.c_str() << std::endl;
      throw std::logic_error(message.c_str());
    }
    // if (systemType ==
    //     static_cast<unsigned short>(IFFSystemType::Mode_5_Interrogator)) {
    //   _layer3M5IF.marshal(dataStream);
    // } else if (systemType ==
    //            static_cast<unsigned
    //            short>(IFFSystemType::Mode_5_Transponder)) {
    //   _layer3M5TF.marshal(dataStream);
    // }
  }
  if (_fundamentalOperationalData.isInformationLayerPresent(4)) {
    if (_layer4 != nullptr) {
      _layer4->discriminator(transponder);
      _layer4->marshal(dataStream);
    } else {
      std::string message(
          "Layer4 has been declared as present, but has not been set!!");
      std::cerr << message.c_str() << std::endl;
      throw std::logic_error(message.c_str());
    }
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
  if (_fundamentalOperationalData.isInformationLayerPresent(2)) {
    _layer2.unmarshal(dataStream);
  }
  bool transponder = _systemID.isTransponder();
  if (_fundamentalOperationalData.isInformationLayerPresent(3)) {
    if (_layer3 == nullptr) {
      _layer3 = new Layer3(transponder);
    } else {
      _layer3->discriminator(transponder);
    }
    _layer3->unmarshal(dataStream);
  }
  if (_fundamentalOperationalData.isInformationLayerPresent(4)) {
    if (_layer4 == nullptr) {
      _layer4 = new Layer4(transponder);
    } else {
      _layer4->discriminator(transponder);
    }
    _layer4->unmarshal(dataStream);
  }
}

bool IFFPdu::operator==(const IFFPdu& rhs) const {
  bool ivarsEqual = true;

  ivarsEqual = DistributedEmissionsFamilyPdu::operator==(rhs);

  if (ivarsEqual && !(_emittingEntityID == rhs._emittingEntityID))
    ivarsEqual = false;
  if (ivarsEqual && !(_eventID == rhs._eventID)) ivarsEqual = false;
  if (ivarsEqual && !(_relativeAntennaLocation == rhs._relativeAntennaLocation))
    ivarsEqual = false;
  if (ivarsEqual && !(_systemID == rhs._systemID)) ivarsEqual = false;
  if (ivarsEqual && !(_systemDesignator == rhs._systemDesignator))
    ivarsEqual = false;
  if (ivarsEqual && !(_systemSpecificData == rhs._systemSpecificData))
    ivarsEqual = false;
  if (ivarsEqual &&
      !(_fundamentalOperationalData == rhs._fundamentalOperationalData))
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
  marshalSize += _emittingEntityID.getMarshalledSize();  // _emittingEntityID
  marshalSize += _eventID.getMarshalledSize();           // _eventID
  marshalSize +=
      _relativeAntennaLocation.getMarshalledSize();  //_relativeAntennaLocation
  marshalSize = marshalSize + _systemID.getMarshalledSize();  //_systemID
  marshalSize = marshalSize + 1;  //_systemDesignator
  marshalSize = marshalSize + 1;  //_systemSpecificData
  marshalSize += _fundamentalOperationalData
                     .getMarshalledSize();  // _fundamentalOperationalData

  if (_fundamentalOperationalData.isInformationLayerPresent(2)) {
    marshalSize += _layer2.getMarshalledSize();
  }
  unsigned short systemType = getSystemID().getSystemType();

  if (_fundamentalOperationalData.isInformationLayerPresent(3)) {
    if (_layer3 != nullptr) {
      marshalSize += _layer3->getMarshalledSize();
    }
  }
  if (_fundamentalOperationalData.isInformationLayerPresent(4)) {
    if (_layer4 != nullptr) {
      marshalSize += _layer4->getMarshalledSize();
    }
  }
  return marshalSize;
}
