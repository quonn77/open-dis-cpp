#include <dis7/IFFPdu.h>
#include <dis7/Layer3.h>

#include <stdexcept>

using namespace DIS;

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All
// rights reserved.
//
// @see Table 169—Layer 3 Mode 5 Interrogator Format page 419 of IEEE Std 1278.1
//
// @author Alessio Iannone, aia

Layer3::Layer3(bool transponder)
    : _layer3Mode5IFpx(nullptr), _layer3Mode5TFpx(nullptr) {
  discriminator(transponder);
}

Layer3::~Layer3() {
  if (_layer3Mode5IFpx != nullptr) {
    delete _layer3Mode5IFpx;
    _layer3Mode5IFpx = nullptr;
  }
  if (_layer3Mode5TFpx != nullptr) {
    delete _layer3Mode5TFpx;
    _layer3Mode5TFpx = nullptr;
  }
}

IPDU* Layer3::getLayer3PDU() const {
  IPDU* pduPx = nullptr;
  switch (_layer3Type) {
    case Layer3Type::Layer3Mode5IF:
      pduPx = _layer3Mode5IFpx;
      break;
    case Layer3Type::Layer3Mode5TF:
      pduPx = _layer3Mode5TFpx;
      break;
    default:
      break;
  }
  return pduPx;
}

Layer3Type Layer3::discriminator() { return _layer3Type; }
Layer3Type Layer3::discriminator() const { return _layer3Type; }
Layer3Mode5IF* Layer3::getLayer3Mode5IF() {
  if (discriminator() != Layer3Type::Layer3Mode5IF) {
    throw std::invalid_argument("Incorrect Layer Type request: " +
                                static_cast<int>(_layer3Type));
  }
  return _layer3Mode5IFpx;
}

void Layer3::discriminator(bool transponder) {
  if (_layer3Mode5TFpx != nullptr) {
    delete _layer3Mode5TFpx;
    _layer3Mode5TFpx = nullptr;
  }
  if (_layer3Mode5IFpx != nullptr) {
    delete _layer3Mode5IFpx;
    _layer3Mode5IFpx = nullptr;
  }
  Layer3Type type;
  if (transponder) {
    type = Layer3Type::Layer3Mode5TF;
    _layer3Mode5TFpx = new Layer3Mode5TF();
  } else {
    type = Layer3Type::Layer3Mode5IF;
    _layer3Mode5IFpx = new Layer3Mode5IF();
  }
  this->_layer3Type = type;
}

Layer3Mode5IF* Layer3::getLayer3Mode5IF() const {
  if (discriminator() != Layer3Type::Layer3Mode5IF) {
    throw std::invalid_argument("Incorrect Layer Type request: " +
                                static_cast<int>(_layer3Type));
  }
  return _layer3Mode5IFpx;
}
void Layer3::setLayer3Mode5IF(Layer3Mode5IF* pX) {
  _layer3Type = Layer3Type::Layer3Mode5IF;
  _layer3Mode5IFpx = pX;
  if (_layer3Mode5TFpx != nullptr) {
    delete _layer3Mode5TFpx;
    _layer3Mode5TFpx = nullptr;
  }
}

Layer3Mode5TF* Layer3::getLayer3Mode5TF() {
  if (discriminator() != Layer3Type::Layer3Mode5TF) {
    throw std::invalid_argument("Incorrect Layer Type request: " +
                                static_cast<int>(_layer3Type));
  }
  return _layer3Mode5TFpx;
}

Layer3Mode5TF* Layer3::getLayer3Mode5TF() const {
  if (discriminator() != Layer3Type::Layer3Mode5TF) {
    throw std::invalid_argument("Incorrect Layer Type request: " +
                                static_cast<int>(_layer3Type));
  }
  return _layer3Mode5TFpx;
}

void Layer3::setLayer3Mode5TF(Layer3Mode5TF* pX) {
  this->_layer3Type = Layer3Type::Layer3Mode5TF;
  this->_layer3Mode5TFpx = pX;
  if (_layer3Mode5IFpx != nullptr) {
    delete _layer3Mode5IFpx;
    _layer3Mode5IFpx = nullptr;
  }
}

void Layer3::marshal(DataStream& dataStream) const {
  IPDU* pduPx = getLayer3PDU();
  if (pduPx != nullptr) {
    pduPx->marshal(dataStream);
  }
}

void Layer3::unmarshal(DataStream& dataStream) {
  IPDU* pduPx = getLayer3PDU();
  if (pduPx != nullptr) {
    pduPx->unmarshal(dataStream);
  }
}

int Layer3::getMarshalledSize() const {
  IPDU* pduPx = getLayer3PDU();
  if (pduPx != nullptr) {
    return pduPx->getMarshalledSize();
  } else {
    return 0;
  }
}

bool Layer3::operator==(const IPDU& rhs) const { IPDU* pduPx = getLayer3PDU(); }

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
