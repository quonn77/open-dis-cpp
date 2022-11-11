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

void initSimulationManagementFamily(DIS::SimulationManagementFamilyPdu& simFamilyPDU, int exerciseID, DIS::SimulationAddress& simAddress) {
    initPduSuperClass(simFamilyPDU, exerciseID);
    simFamilyPDU.getOriginatingEntityID().setSimulationAddress(simAddress);
    simFamilyPDU.getOriginatingEntityID().setEntityNumber(100);

    simFamilyPDU.getReceivingEntityID().setSimulationAddress(simAddress);
    simFamilyPDU.getReceivingEntityID().setEntityNumber(200);
}

void testSetData(DIS::SimulationAddress& simAddress, int exerciseID) {
    std::cout << std::endl << "================ Test SetData PDU ================= " << std::endl;
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
    unsigned char variablePayload[9];
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
              << " Fixed Datum ID: " << setData.getFixedDatums().at(0).getFixedDatumID()
              << " Variable Datum ID: " << setData.getVariableDatums()[0].getVariableDatumID() << std::endl;
    DIS::VariableDatum& variableDatumRef = setData.getVariableDatums()[0];
    std::cout << " Variable datum = " << variableDatumRef.getPayLoad() << std::endl;

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
        std::cout << "Valid SetData PDU Marshall/Unmarshall operation " << std::endl;
    } else {
        std::cout << "Wrong SetData PDU Marshall/Unmarshall operation " << std::endl;
    }
}

void testStartResume(DIS::SimulationAddress& simAddress, int exerciseID) {
    std::cout << std::endl << "================ Test Start/Resume PDU ================= " << std::endl;
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
        std::cout << "Valid StartResumePDU  marshalling & unmarshalling" << std::endl;
    } else {
        std::cerr << "Wrong StartResumePDU marshalling&unmarshalling" << std::endl;
    }
}

void testStopFreeze(DIS::SimulationAddress& simAddress, int exerciseID) {
    std::cout << std::endl << "================ Test Stop/Freeze PDU ================= " << std::endl;

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
        std::cout << "Valid StopFreezePdu  marshalling & unmarshalling" << std::endl;
    } else {
        std::cerr << "Wrong StopFreezePdu marshalling&unmarshalling" << std::endl;
    }
}

int main(int argc, char* argv[]) {

    DIS::SimulationAddress simAddress;
    simAddress.setSite(1);
    simAddress.setApplication(2);

    testSetData(simAddress, 1);
    testStartResume(simAddress, 2);
    testStopFreeze(simAddress, 3);
}