#pragma once

#include <dis7/BeamData.h>
#include <dis7/DistributedEmissionsFamilyPdu.h>
#include <dis7/EntityID.h>
#include <dis7/EventIdentifier.h>
#include <dis7/FundamentalOperationalData.h>
#include <dis7/IFFFundamentalParameterData.h>
#include <dis7/Layer2.h>
#include <dis7/Layer3.h>
#include <dis7/Layer4.h>
#include <dis7/LayerHeader.h>
#include <dis7/SecondaryOperationalData.h>
#include <dis7/SystemIdentifier.h>
#include <dis7/Vector3Float.h>
#include <dis7/msLibMacro.h>
#include <utils/DataStream.h>

#include <vector>

namespace DIS {
// This PDU is written according SISO Standard, the link is on below:
// https://www.sisostds.org/DesktopModules/Bring2mind/DMX/API/Entries/Download?Command=Core_Download&EntryId=36292&PortalId=0&TabId=105
// Another good document for DIS v6 and v7 is:
// https://www.sisostds.org/DesktopModules/Bring2mind/DMX/API/Entries/Download?Command=Core_Download&EntryId=29289&PortalId=0&TabId=105

// @author semihkurt , 09/04/2021
// @author Alessio Iannone 21/11/2021 quonn77@gmail.com


class EXPORT_MACRO IFFPdu : public DistributedEmissionsFamilyPdu {
 protected:
  /** ID of the entity emitting */
  EntityID _emittingEntityID;

  /** ID of event */
  EventIdentifier _eventID;

  Vector3Float _relativeAntennaLocation;

  /** How many iff parameters are in the variable length list */
  unsigned int _numberOfIFFParameters;

  SystemIdentifier _systemID;

  unsigned char _systemDesignator;

  unsigned char _systemSpecificData;

  FundamentalOperationalData _fundamentalOperationalData;

  /// Check informationLayers of FundamentalOperationalData
  /// to verify if the layer is active or not
  Layer2 _layer2;
  Layer3* _layer3;

  Layer4* _layer4;
  // Layer3Mode5IF _layer3M5IF;
  //  Verify on Layer1 SystemType if it is the transponder format
  //  Layer3Mode5TF _layer3M5TF;
  //  Layer4ModeSIF _layer4MSIF;
  //  Layer4ModeSTF _layer4MSTF;

 public:
  IFFPdu();
  virtual ~IFFPdu();

  virtual void marshal(DataStream& dataStream) const;
  virtual void unmarshal(DataStream& dataStream);

  EntityID& getEmittingEntityID();
  const EntityID& getEmittingEntityID() const;
  void setEmittingEntityID(const EntityID& pX);

  EventIdentifier& getEventID();
  const EventIdentifier& getEventID() const;
  void setEventID(const EventIdentifier& pX);

  Vector3Float& getRelativeAntennaLocation();
  const Vector3Float& getRelativeAntennaLocation() const;
  void setRelativeAntennaLocation(const Vector3Float& pX);

  unsigned int getNumberOfIFFParameters() const;

  SystemIdentifier& getSystemID();
  const SystemIdentifier& getSystemID() const;
  void setSystemID(const SystemIdentifier& pX);

  unsigned char getSystemDesignator() const;
  void setSystemDesignator(unsigned char pX);

  unsigned char getSystemSpecificData() const;
  void setSystemSpecificData(unsigned char pX);

  FundamentalOperationalData& getFundamentalOperationalData();
  const FundamentalOperationalData& getFundamentalOperationalData() const;
  void setFundamentalOperationalData(const FundamentalOperationalData& pX);

  Layer2& getLayer2();
  const Layer2& getLayer2() const;
  void setLayer2(const Layer2& pX);

  Layer3* getLayer3();
  Layer3* getLayer3() const;
  void setLayer3(Layer3* pX);

  /**
   * @brief Get the Layer4 object
   *
   * This is valid only if layer 4 is present
   * @return Layer4&
   */
  Layer4* getLayer4();
  Layer4* getLayer4() const;
  void setLayer4(Layer4* pX);

  // /**
  //  * @brief Get the Layer3 Mode5 IF object.
  //  *
  //  * This is valid only if layer3 is present
  //  * and the IFF system type is of type
  //  * Mode_5_Interrogator
  //  *
  //  * @return Layer3Mode5IF&
  //  */
  // Layer3Mode5IF& getLayer3Mode5IF();
  // const Layer3Mode5IF& getLayer3Mode5IF() const;
  // void setLayer3Mode5IF(const Layer3Mode5IF& pX);

  // /**
  //  * @brief Get the Layer3 Mode5 TF object.
  //  *
  //  * This is valid only if layer3 is present
  //  * and the IFF system type is of type
  //  * Mode_5_Transponder
  //  *
  //  * @return Layer3Mode5TF&
  //  */
  // Layer3Mode5TF& getLayer3Mode5TF();
  // const Layer3Mode5TF& getLayer3Mode5TF() const;
  // void setLayer3Mode5TF(const Layer3Mode5TF& pX);

  // /**
  //  * @brief Get the Layer4 ModeS IF object.
  //  *
  //  * This is valid only if layer 4 is present
  //  * and the IFF system type is of type
  //  * Mode_S_Interrogator
  //  *
  //  * @return Layer4ModeSIF&
  //  */
  // Layer4ModeSIF& getLayer4ModeSIF();
  // const Layer4ModeSIF& getLayer4ModeSIF() const;
  // void setLayer4ModeSIF(const Layer4ModeSIF& pX);

  // /**
  //  * @brief Get the Layer4 Mode S TF object.
  //  *
  //  * This is valid only if layer 4 is present
  //  * and the IFF system type is of type
  //  * Mode_S_Transponder
  //  *
  //  * @return Layer4ModeSTF&
  //  */
  // Layer4ModeSTF& getLayer4ModeSTF();
  // const Layer4ModeSTF& getLayer4ModeSTF() const;
  // void setLayer4ModeSTF(const Layer4ModeSTF& pX);

  virtual int getMarshalledSize() const;

  bool operator==(const IFFPdu& rhs) const;
};
}  // namespace DIS
