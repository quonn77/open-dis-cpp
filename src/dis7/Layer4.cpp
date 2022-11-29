#include <dis7/Layer4.h>
#include <dis7/IFFPdu.h>
#include <stdexcept>

using namespace DIS;

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All
// rights reserved.
//
// @see Table 169—Layer 3 Mode 5 Interrogator Format page 419 of IEEE Std 1278.1
//
// @author Alessio Iannone, aia

Layer4::Layer4(bool transponder)
    : _layer4ModeSIFpx(nullptr), _layer4ModeSTFpx(nullptr) {
  discriminator(transponder);
}

Layer4::~Layer4() {
  if (_layer4ModeSIFpx != nullptr) {
    delete _layer4ModeSIFpx;
  }
  if (_layer4ModeSTFpx != nullptr) {
    delete _layer4ModeSTFpx;
  }
}

IPDU* Layer4::getLayer4PDU() const {
  IPDU* pduPx = nullptr;
  switch (_layer4Type) {
    case Layer4Type::Layer4ModeSIF:
      pduPx = _layer4ModeSIFpx;
      break;
    case Layer4Type::Layer4ModeSTF:
      pduPx = _layer4ModeSTFpx;
      break;
    default:
      break;
  }
  return pduPx;
}

Layer4Type Layer4::discriminator() { return _layer4Type; }
Layer4Type Layer4::discriminator() const { return _layer4Type; }
Layer4ModeSIF* Layer4::getLayer4ModeSIF() {
  if (discriminator() != Layer4Type::Layer4ModeSIF) {
    throw std::invalid_argument("Incorrect Layer Type request: " +
                                static_cast<int>(_layer4Type));
  }
  return _layer4ModeSIFpx;
}
void Layer4::discriminator(bool transponder) {
  if (_layer4ModeSIFpx != nullptr) {
    delete _layer4ModeSIFpx;
    _layer4ModeSIFpx = nullptr;
  }
  if (_layer4ModeSTFpx != nullptr) {
    delete _layer4ModeSIFpx;
    _layer4ModeSIFpx = nullptr;
  }

  
  Layer4Type type;
  if(transponder){
  type = Layer4Type::Layer4ModeSTF;
      _layer4ModeSTFpx = new Layer4ModeSTF();
  }else{
 type = Layer4Type::Layer4ModeSIF;
      _layer4ModeSIFpx = new Layer4ModeSIF();
  }
  this->_layer4Type = type;
}
Layer4ModeSIF* Layer4::getLayer4ModeSIF() const {
  if (discriminator() != Layer4Type::Layer4ModeSIF) {
    throw std::invalid_argument("Incorrect Layer Type request: " +
                                static_cast<int>(_layer4Type));
  }
  return _layer4ModeSIFpx;
}
void Layer4::setLayer4ModeSIF(Layer4ModeSIF* pX) {
  _layer4Type = Layer4Type::Layer4ModeSIF;
  _layer4ModeSIFpx = pX;
  if (_layer4ModeSTFpx != nullptr) {
    delete _layer4ModeSTFpx;
    _layer4ModeSTFpx = nullptr;
  }
}

Layer4ModeSTF* Layer4::getLayer4ModeSTF() {
  if (discriminator() != Layer4Type::Layer4ModeSTF) {
    throw std::invalid_argument("Incorrect Layer Type request: " +
                                static_cast<int>(_layer4Type));
  }
  return _layer4ModeSTFpx;
}

Layer4ModeSTF* Layer4::getLayer4ModeSTF() const {
  if (discriminator() != Layer4Type::Layer4ModeSTF) {
    throw std::invalid_argument("Incorrect Layer Type request: " +
                                static_cast<int>(_layer4Type));
  }
  return _layer4ModeSTFpx;
}

void Layer4::setLayer4ModeSTF(Layer4ModeSTF* pX) {
  this->_layer4Type = Layer4Type::Layer4ModeSTF;
  this->_layer4ModeSTFpx = pX;
  if (this->_layer4ModeSIFpx != nullptr) {
    delete _layer4ModeSIFpx;
    _layer4ModeSIFpx = nullptr;
  }
}

void Layer4::marshal(DataStream& dataStream) const {
  IPDU* pduPx = getLayer4PDU();
  if (pduPx != nullptr) {
    pduPx->marshal(dataStream);
  }
}

void Layer4::unmarshal(DataStream& dataStream) {
  IPDU* pduPx = getLayer4PDU();
  if (pduPx != nullptr) {
    pduPx->unmarshal(dataStream);
  }
}

int Layer4::getMarshalledSize() const {
  IPDU* pduPx = getLayer4PDU();
  if (pduPx != nullptr) {
    return pduPx->getMarshalledSize();
  } else {
    return 0;
  }
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
