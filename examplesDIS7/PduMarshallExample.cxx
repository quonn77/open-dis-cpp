#include <dis7/DataPdu.h>
#include <dis7/IFFPdu.h>
#include <dis7/SetDataPdu.h>
#include <dis7/StartResumePdu.h>
#include <dis7/StopFreezePdu.h>

#include <ctime>
#include <iostream>
#include <string>

#include "assert.h"

void initPduSuperClass(DIS::PduSuperclass& pduSuperClass, int exerciseID) {
  std::time_t time = std::time(NULL);
  pduSuperClass.setTimestamp(time);
  pduSuperClass.setExerciseID(exerciseID);
}

void initSimulationManagementFamily(
    DIS::SimulationManagementFamilyPdu& simFamilyPDU, int exerciseID,
    DIS::SimulationAddress& simAddress) {
  initPduSuperClass(simFamilyPDU, exerciseID);
  simFamilyPDU.getOriginatingEntityID().setSimulationAddress(simAddress);
  simFamilyPDU.getOriginatingEntityID().setEntityNumber(100);

  simFamilyPDU.getReceivingEntityID().setSimulationAddress(simAddress);
  simFamilyPDU.getReceivingEntityID().setEntityNumber(200);
}

void testSetData(DIS::SimulationAddress& simAddress, int exerciseID) {
  std::cout << std::endl
            << "================ Test SetData PDU ================= "
            << std::endl;
  DIS::SetDataPdu setData;
  initSimulationManagementFamily(setData, exerciseID, simAddress);
  setData.setPduStatus(6);
  setData.setRequestID(123);
  DIS::FixedDatum fixedDatum;
  fixedDatum.setFixedDatumID(100);
  fixedDatum.setFixedDatumValue(200);
  setData.getFixedDatums().push_back(fixedDatum);

  DIS::VariableDatum variableDatum;
  variableDatum.setVariableDatumID(400);
  char variablePayload[9];
  variablePayload[0] = 'c';
  variablePayload[1] = 'i';
  variablePayload[2] = 'a';
  variablePayload[3] = 'o';
  variablePayload[4] = 'm';
  variablePayload[5] = 'i';
  variablePayload[6] = 'a';
  variablePayload[7] = 'o';
  variablePayload[8] = 'k';

  variablePayload[0] = 0b01110111;
  variablePayload[1] = 0b01110111;
  variablePayload[2] = 0b01110111;
  variablePayload[3] = 0b01110111;
  variablePayload[4] = 0b01110111;
  variablePayload[5] = 0b01110111;
  variablePayload[6] = 0b01110111;
  variablePayload[7] = 0b01110111;
  variablePayload[8] = 0b01110001;

  variableDatum.setPayLoad(variablePayload, 9);
  variableDatum.setVariableDatumLength(65);

  setData.getVariableDatums().push_back(variableDatum);
  std::cout << "Exercise ID=" << std::to_string(setData.getExerciseID())
            << " Fixed Datum ID: "
            << setData.getFixedDatums().at(0).getFixedDatumID()
            << " Variable Datum ID: "
            << setData.getVariableDatums()[0].getVariableDatumID() << std::endl;
  DIS::VariableDatum& variableDatumRef = setData.getVariableDatums()[0];
  std::cout << " Variable datum = " << variableDatumRef.getPayLoad()
            << std::endl;

  DIS::DataStream buffer(DIS::BIG);
  setData.marshal(buffer);

  /* for (int i = 0; i < buffer.size(); i++) {
   printf("%X ", (unsigned char)buffer[i]);
 }
*/
  DIS::SetDataPdu data;
  data.unmarshal(buffer);

  assert(data.getExerciseID() == 1);
  assert(data == setData);
  if (data == setData) {
    std::cout << "Valid SetData PDU Marshall/Unmarshall operation "
              << std::endl;
  } else {
    std::cout << "Wrong SetData PDU Marshall/Unmarshall operation "
              << std::endl;
  }
}

void testStartResume(DIS::SimulationAddress& simAddress, int exerciseID) {
  std::cout << std::endl
            << "================ Test Start/Resume PDU ================= "
            << std::endl;
  DIS::StartResumePdu startResumePDU;
  initSimulationManagementFamily(startResumePDU, exerciseID, simAddress);
  DIS::ClockTime clock;
  DIS::ClockTime clockSim;
  clock.setHour(24);
  clock.setTimePastHour(10);

  clockSim.setHour(12);
  clockSim.setTimePastHour(1);
  startResumePDU.setRealWorldTime(clock);
  startResumePDU.setSimulationTime(clockSim);
  startResumePDU.setRequestID(200);

  DIS::DataStream stream(DIS::BIG);
  startResumePDU.marshal(stream);

  DIS::StartResumePdu unmarshallPDU;
  unmarshallPDU.unmarshal(stream);

  assert(unmarshallPDU.getExerciseID() == exerciseID);
  assert(unmarshallPDU.getRealWorldTime() == clock);
  assert(unmarshallPDU.getSimulationTime() == clockSim);
  assert(unmarshallPDU.getRequestID() == 200);

  if (startResumePDU == unmarshallPDU) {
    std::cout << "Valid StartResumePDU  marshalling & unmarshalling"
              << std::endl;
  } else {
    std::cerr << "Wrong StartResumePDU marshalling&unmarshalling" << std::endl;
  }
}
void testDataPDU(DIS::SimulationAddress& simAddress, int exerciseID) {
  std::cout << std::endl
            << "================ Test Data PDU ================= " << std::endl;
  DIS::DataPdu dataPdu;
  initSimulationManagementFamily(dataPdu, exerciseID, simAddress);
  DIS::FixedDatum fixedDatum;
  fixedDatum.setFixedDatumID(100);
  fixedDatum.setFixedDatumValue(20);
  dataPdu.getFixedDatums().push_back(fixedDatum);

  DIS::FixedDatum fixedDatum2;
  fixedDatum2.setFixedDatumID(200);
  fixedDatum2.setFixedDatumValue(40);
  dataPdu.getFixedDatums().push_back(fixedDatum2);

  DIS::VariableDatum variableDatum;
  int payLoadSize = 21;
  char* payLoad = new char[payLoadSize];
  memset(payLoad, 0, payLoadSize);

  DIS::DataStream dataStream(DIS::BIG);
  dataStream << (double)20;
  dataStream << 1;
  dataStream << 'c';
  dataStream << std::string("ciao");
  dataStream.copToByteBuffer(payLoad);

  variableDatum.setPayLoad(payLoad, payLoadSize);
  variableDatum.setVariableDatumID(20);

  dataPdu.getVariableDatums().push_back(variableDatum);

  DIS::DataStream buffer(DIS::BIG);
  dataPdu.marshal(buffer);

  DIS::DataPdu dataBack;
  dataBack.unmarshal(buffer);

  assert(dataBack.getExerciseID() == exerciseID);
  assert(dataBack.getFixedDatums()[0].getFixedDatumID() == 100);
  assert(dataBack.getFixedDatums()[0].getFixedDatumValue() == 20);
  assert(dataBack.getFixedDatums()[1].getFixedDatumID() == 200);
  assert(dataBack.getFixedDatums()[1].getFixedDatumValue() == 40);
  assert(dataBack.getVariableDatums()[0].getVariableDatumID() == 20);
  char* dataPayload = dataBack.getVariableDatums()[0].getPayLoad(false);
  DIS::DataStream dataStreamPayload(dataPayload, payLoadSize, DIS::BIG);
  double data1;
  int data2;
  char data3;
  std::string data4("");
  dataStreamPayload >> data1;
  dataStreamPayload >> data2;
  dataStreamPayload >> data3;
  dataStreamPayload >> data4;
  std::cout << "Data 1 = " << std::to_string(data1) << std::endl;
  std::cout << "Data 2 = " << std::to_string(data2) << std::endl;
  std::cout << "Data 3 = " << data3 << std::endl;
  std::cout << "Data 4 = " << data4.c_str() << std::endl;
  assert(data1 == (double)20);
  assert(data2 == 1);
  assert(data3 == 'c');
  assert(dataBack == dataPdu);
  std::cout << "Valid DataPdu Marshalling & Unmarshalling" << std::endl;
}
void testIFFPDU(DIS::SimulationAddress& simAddress, int exerciseID) {
  std::cout << std::endl
            << "================ Test IFF PDU ================= " << std::endl;
  DIS::IFFPdu iffPdu;
  iffPdu.setPduStatus(9);
  iffPdu.setExerciseID(exerciseID);
  iffPdu.getEventID().setEventNumber(exerciseID * 2);
  iffPdu.getEventID().getSimulationAddress().setApplication(10);
  iffPdu.getEventID().getSimulationAddress().setSite(20);

  // Enable layer 1,2,3,4
  unsigned char infoLayers = 1 << 1;
  infoLayers |= (1 << 2);
  infoLayers |= (1 << 3);
  infoLayers |= (1 << 4);

  DIS::SystemIdentifier& systemID = iffPdu.getSystemID();
  DIS::FundamentalOperationalData& fundamentalData =
      iffPdu.getFundamentalOperationalData();

  fundamentalData.setInformationLayers(infoLayers);
  systemID.setSystemType(
      static_cast<unsigned short>(DIS::IFFSystemType::Mode_5_Transponder));

  assert(systemID.isTransponder() == true);
  std::cout << "IFF is transponder: "
            << std::to_string(systemID.isTransponder()) << std::endl;
  // Mark as interrogator
  systemID.setChangeOptions(systemID.getChangeOptions() | (1 << 4));
  systemID.setSystemType(
      static_cast<unsigned short>(DIS::IFFSystemType::Mode_5_Interrogator));

  assert(systemID.isTransponder() == false);

  /**
   * Mark as interrogator, please note this will not update accordingly the
   * change options
   *
   */
  systemID.setSystemType(DIS::IFFSystemType::Mark_X_XII_ATCRBS_Transponder);
  std::cout << "IFF is transponder: "
            << std::to_string(systemID.isTransponder()) << std::endl;

  assert(systemID.isTransponder() == true);

  systemID.setSystemType(DIS::IFFSystemType::Mark_X_XII_ATCRBS_Interrogator);
  std::cout << "IFF is transponder: "
            << std::to_string(systemID.isTransponder()) << std::endl;

  assert(systemID.isTransponder() == false);
  assert(iffPdu.getLayer3() == nullptr);
  assert(iffPdu.getLayer4() == nullptr);
  assert(fundamentalData.isInformationLayerPresent(1) == true);
  assert(fundamentalData.isInformationLayerPresent(2) == true);
  assert(fundamentalData.isInformationLayerPresent(3) == true);
  assert(fundamentalData.isInformationLayerPresent(4) == true);
  assert(fundamentalData.isInformationLayerPresent(5) == false);

  DIS::Layer3* layer3px = new DIS::Layer3(systemID.isTransponder());
  iffPdu.setLayer3(layer3px);
  assert(iffPdu.getLayer3() != nullptr);

  std::cout << "IFF is transponder: "
            << std::to_string(systemID.isTransponder()) << std::endl;

  DIS::Layer4* layer4px = new DIS::Layer4(systemID.isTransponder());
  DIS::Layer4ModeSIF* modeSIF =
      dynamic_cast<DIS::Layer4ModeSIF*>(layer4px->getLayer4PDU());
  std::cout << "Layer4 Mode address: " << std::hex << modeSIF << std::endl;
  std::cout << "Layer4 Mode address: "
            << std::to_string(modeSIF->getNumberOfIffRecords()) << std::endl;
  layer4px->getLayer4ModeSIF()
      ->getModeSInterrogatorBasicData()
      .setModeSLevelPresent(5);
  iffPdu.setLayer4(layer4px);
  std::cout << "Set - Layer 4 Mode S Level Present:"
            << std::to_string((iffPdu.getLayer4()
                                   ->getLayer4ModeSIF()
                                   ->getModeSInterrogatorBasicData()
                                   .getModeSLevelPresent()))
            << std::endl;

  assert(iffPdu.getExerciseID() == exerciseID);

  DIS::DataStream buffer(DIS::BIG);
  iffPdu.marshal(buffer);

  DIS::IFFPdu backPDU;
  backPDU.unmarshal(buffer);

  assert(iffPdu == backPDU);

  if (iffPdu == backPDU) {
    std::cout << "Valid IFFPdu  marshalling & unmarshalling" << std::endl;
  } else {
    std::cerr << "Wrong IFFPdu marshalling&unmarshalling" << std::endl;
  }
}
void testStopFreeze(DIS::SimulationAddress& simAddress, int exerciseID) {
  std::cout << std::endl
            << "================ Test Stop/Freeze PDU ================= "
            << std::endl;

  DIS::StopFreezePdu stopFreezePDU;
  initSimulationManagementFamily(stopFreezePDU, exerciseID, simAddress);
  DIS::ClockTime clock;
  clock.setHour(24);
  clock.setTimePastHour(10);
  stopFreezePDU.setRealWorldTime(clock);
  stopFreezePDU.setReason(100);
  stopFreezePDU.setFrozenBehavior(200);
  stopFreezePDU.setRequestID(300);

  DIS::DataStream stream(DIS::BIG);
  stopFreezePDU.marshal(stream);

  DIS::StopFreezePdu unmarshallPDU;
  unmarshallPDU.unmarshal(stream);

  if (stopFreezePDU == unmarshallPDU) {
    std::cout << "Valid StopFreezePdu  marshalling & unmarshalling"
              << std::endl;
  } else {
    std::cerr << "Wrong StopFreezePdu marshalling&unmarshalling" << std::endl;
  }
}

int main(int argc, char* argv[]) {
  // if (argc > 1) {
  //     std::cout << "argc = "<<std::to_string(argc)<<" - "<<argv[0] <<
  //     std::endl;
  // }else{
  //     return -1;
  // }
  DIS::SimulationAddress simAddress;
  simAddress.setSite(1);
  simAddress.setApplication(2);

  testSetData(simAddress, 1);
  testStartResume(simAddress, 2);
  testStopFreeze(simAddress, 3);
  testDataPDU(simAddress, 4);
  testIFFPDU(simAddress, 5);
  return 0;
}