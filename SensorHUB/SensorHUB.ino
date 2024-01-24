#include <Wire.h>
#include "wiring_private.h"  // pinPeripheral() function
#include "pinTools.h"

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

#define TEMP_MODULE_ADDR 0x2A
#define ledHb 14

unsigned long lastLedFlash = 0;

bool ledLevel = false;

// SDA will be on SERCOM1.0 D11 and SCL will be on SERCOM1.1 D13

// Default Wire:
// I2C / SERCOM 0:
// PA22 / SDA on pin 11;
// PA23 / SCL on pin 12;

// On the Development Board:
// D13_SCL_PA17 /﻿D11_SDA_PA16
// D3_SCL_PA09 / D4_SDA_PA08
// SCL_PA23 / SDA_PA22 are they mixed up? Needs checking Nov 5, 2021. SFM Could be switched using jumper wires on the pads JP9/JP10

TwoWire WireBackbone(&sercom3, W0_SDA, W0_SCL);  // Main
TwoWire WireSensorA(&sercom1, W1_SDA, W1_SCL);   // Sensor A
TwoWire WireSensorB(&sercom4, W2_SDA, W2_SCL);   // Sensor B
// And of course standard Wire


void setup() {
  delay(500);
  Serial.begin(115200);
  delay(500);

  Wire.begin();
  WireBackbone.begin(0x2B);
  WireSensorA.begin();
  WireSensorB.begin();

  pinMode(ledHb, OUTPUT);
  digitalWrite(ledHb, HIGH);

  portBackbone.setPinPeripheralStates();
  portSensorsA.setPinPeripheralAltStates();
  portSensorsB.setPinPeripheralStates();

  while (!Serial)
    ;

  Serial.println("Ready...");
  delay(1500);
  digitalWrite(ledHb, LOW);
}


void loop() {
  digitalWrite(ledHb, HIGH);
  //boolean result = reportDevicesWithAddressOn(&WireBackbone, 0x60, true);  // 0x10 is maybe finger position sensor.

  //reportDevicesOn(&WireBackbone, "Mainbus");
  reportDevicesOn(&WireSensorA, "Sensors Ax");
  reportDevicesOn(&WireSensorB, "Sensors Bx");

  delay(500);  // wait 5 seconds for next scan
  digitalWrite(ledHb, LOW);
  delay(500);  // wait 5 seconds for next scan
}

void reportDevicesOn(TwoWire *wire, String label) {
  byte error, address;
  int nDevices;
  Serial.print("Scanning bus ");
  Serial.println(label);
  for (address = 1; address < 127; address++) {
    digitalWrite(ledHb, LOW);
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.

    //wire->beginTransmission(address);
    //error = wire->endTransmission();

    if (reportDevicesWithAddressOn(wire, address)) {
      digitalWrite(ledHb, HIGH);
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      if (address == TEMP_MODULE_ADDR) {
        readADC(wire, 1);
      }

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found on bus 1\n");
  else
    Serial.println("done\n");
}



boolean reportDevicesWithAddressOn(TwoWire *wire, byte deviceAddress) {
  wire->beginTransmission(deviceAddress);
  byte error = wire->endTransmission();
  boolean result = (error == 0);
  return result;
}

boolean reportDevicesWithAddressOn(TwoWire *wire, byte deviceAddress, boolean report) {
  wire->beginTransmission(deviceAddress);
  byte error = wire->endTransmission();
  boolean result = (error == 0);
  char buffer[40];
  if (report) {
    if (result) {
      sprintf(buffer, "Device was found on address 0x%02X", deviceAddress);
    } else {
      sprintf(buffer, "No device was found on address 0x%02X", deviceAddress);
    }
    Serial.println(buffer);
  }
  return result;
}


void readADC(TwoWire *wire, byte channel) {

  wire->requestFrom(TEMP_MODULE_ADDR, 3);  // Read 3 bytes from MCP3426
  if (wire->available() >= 3) {
    int firstByte = wire->read();
    int secondByte = wire->read();
    int thirdByte = wire->read();

    // Print the ADC value for the specific channel
    Serial.println(firstByte);
    Serial.println(secondByte);
    Serial.println(thirdByte);
  }
}
