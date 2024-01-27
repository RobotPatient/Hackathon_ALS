//
// Created by emiel on 25-1-2024.
//

#ifndef NIBP_CLION_EASE_I2C_H
#define NIBP_CLION_EASE_I2C_H

#include <Wire.h>
#include "wiring_private.h"  // pinPeripheral() function
#include "pinTools.h"

#define MODULE_ADDR 0x2A

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

// SDA will be on SERCOM1.0 D11 and SCL will be on SERCOM1.1 D13

// Default Wire:
// I2C / SERCOM 0:
// PA22 / SDA on pin 11;
// PA23 / SCL on pin 12;

// On the Development Board:
// D13_SCL_PA17 /D11_SDA_PA16
// D3_SCL_PA09 / D4_SDA_PA08
// SCL_PA23 / SDA_PA22 are they mixed up? Needs checking Nov 5, 2021. SFM Could be switched using jumper wires on the pads JP9/JP10

TwoWire WireBackbone(&sercom3, W0_SDA, W0_SCL);  // Main
TwoWire WireSensorA(&sercom1, W1_SDA, W1_SCL);   // Sensor A
TwoWire WireSensorB(&sercom4, W2_SDA, W2_SCL);   // Sensor B
// And of course standard Wire

#define PRES_MODULE_ADDR 0x68
#define ledHb 14

unsigned long lastLedFlash = 0;

bool ledLevel = false;

void initI2C();
void requestEvent();

void initBus();
void runSens();
void reportDevicesOn(TwoWire *wire, byte address, String label);
void printDeviceName(int address);
boolean reportDevicesWithAddressOn(TwoWire *wire, byte deviceAddress);
boolean reportDevicesWithAddressOn(TwoWire *wire, byte deviceAddress, boolean report);
void readADC(TwoWire *wire, byte channel);

#endif //NIBP_CLION_EASE_I2C_H
