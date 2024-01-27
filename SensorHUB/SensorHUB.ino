#include <Wire.h>
#include "wiring_private.h"  // pinPeripheral() function
#include "pinTools.h"

#include "Sensor.hpp"

// i2c system bus
#define W0_SCL 27  // PA22
#define W0_SDA 26  // PA23

#define W1_SCL 39  // PA13
#define W1_SDA 28  // PA12

#define W2_SCL 13  // PA17
#define W2_SDA 11  // PA16

TwiPinPair portBackbone = TwiPinPair(W0_SCL, W0_SDA);
TwiPinPair portSensorsA = TwiPinPair(W1_SCL, W1_SDA);
TwiPinPair portSensorsB = TwiPinPair(W2_SCL, W2_SDA);

#define ECG_MODULE_ADDR 0x2A
#define TEMP_PRES_MODULE_ADDR 0x68
#define ledHb 14

#define updateCycle 100

byte responseData = 0;

unsigned long lastLedFlash = 0;

bool ledLevel = false;

TwoWire WireBackbone(&sercom3, W0_SDA, W0_SCL);  // Main
TwoWire WireSensorA(&sercom1, W1_SDA, W1_SCL);   // Sensor A
TwoWire WireSensorB(&sercom4, W2_SDA, W2_SCL);   // Sensor B

Sensor tempSens1(TEMP_PRES_MODULE_ADDR, &WireSensorA, 500, 4000);
Sensor tempSens2(TEMP_PRES_MODULE_ADDR, &WireSensorB, 500, 4000);
Sensor ECG_LL(ECG_MODULE_ADDR, &WireSensorA, 0, 2);
Sensor ECG_LA(ECG_MODULE_ADDR, &WireSensorA, 0, 2);
Sensor ECG_RA(ECG_MODULE_ADDR, &WireSensorA, 0, 2);

void setup() {
  Wire.begin(0x2B);
  WireSensorA.begin();
  WireSensorB.begin();

  pinMode(ledHb, OUTPUT);
  digitalWrite(ledHb, HIGH);

  portSensorsA.setPinPeripheralAltStates();
  portSensorsB.setPinPeripheralStates();

  Wire.onRequest(requestEvent);
}

void loop() {
  int16_t tempSens1Waarde = 0;
  int16_t tempSens2Waarde = 0;
  int16_t ECG_LLWaarde = 0;
  int16_t ECG_LAWaarde = 0;
  int16_t ECG_RAWaarde = 0;


  tempSens1.wireObject->requestFrom(tempSens1.deviceAddress, 2);
  if (tempSens1.wireObject->available()) {
    byte waarde1 = tempSens1.wireObject->read();
    byte waarde2 = tempSens1.wireObject->read();
    tempSens1Waarde = ((waarde1 & 0x0F) << 8) | (waarde2);
  }

  tempSens2.wireObject->requestFrom(tempSens2.deviceAddress, 2);
  if (tempSens2.wireObject->available()) {
    byte waarde1 = tempSens2.wireObject->read();
    byte waarde2 = tempSens2.wireObject->read();
    tempSens2Waarde = ((waarde1 & 0x0F) << 8) | (waarde2);
  }

  ECG_LL.wireObject->requestFrom(ECG_LL.deviceAddress, 3);
  if (ECG_LL.wireObject->available()) {
    ECG_LLWaarde = ECG_LL.wireObject->read();
    ECG_LAWaarde = ECG_LL.wireObject->read();
    ECG_RAWaarde = ECG_LL.wireObject->read();
  }

  responseData = 0;
  responseData |= (tempSens1.isCableConnected(tempSens1Waarde));
  responseData |= (tempSens2.isCableConnected(tempSens2Waarde) << 1);
  responseData |= (ECG_LL.howCableConnected(ECG_LLWaarde) << 2);
  responseData |= (ECG_LA.howCableConnected(ECG_LAWaarde) << 4);
  responseData |= (ECG_RA.howCableConnected(ECG_RAWaarde) << 6);

  digitalWrite(ledHb, HIGH);
  delay(updateCycle/2);
  digitalWrite(ledHb, LOW);
  delay(updateCycle/2);
}

void requestEvent() {
  Wire.write(responseData);
}
