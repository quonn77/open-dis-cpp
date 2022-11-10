#include <dis7/SetDataPdu.h>

#include <ctime>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  DIS::SetDataPdu setData;
  setData.setExerciseID(1);
  setData.setProtocolVersion(7);
  std::time_t result = std::time(NULL);
  setData.setTimestamp(result);
  setData.setPduStatus(6);

  DIS::SimulationAddress simAddress;
  simAddress.setSite(1);
  simAddress.setApplication(2);

  setData.getOriginatingEntityID().setEntityNumber(10);
  setData.getOriginatingEntityID().setSimulationAddress(simAddress);

  setData.getReceivingEntityID().setEntityNumber(20);
  setData.getReceivingEntityID().setSimulationAddress(simAddress);
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
  variableDatum.setPayLoad(variablePayload, 9);

  setData.getVariableDatums().push_back(variableDatum);
  std::cout << "Exercise ID=" << std::to_string(setData.getExerciseID())
            << " Fixed Datum ID: "
            << setData.getFixedDatums().at(0).getFixedDatumID()
            << " Variable Datum ID: "
            << setData.getVariableDatums()[0].getVariableDatumID() << std::endl;
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

  std::cout << "\nBack - Exercise ID=" << std::to_string(data.getExerciseID())
            << std::endl;
  if (data == setData) {
    std::cout << "Object are equals " << std::endl;
  } else {
    std::cout << "Object are not equals " << std::endl;
  }
}