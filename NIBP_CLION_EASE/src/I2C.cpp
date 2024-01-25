//
// Created by emiel on 25-1-2024.
//

//#include "I2C.h"

//void initBus()
//{
//    Wire.begin();
//    WireBackbone.begin();
//    WireSensorA.begin();
//    WireSensorB.begin();
//
//    portBackbone.setPinPeripheralStates();
//    portSensorsA.setPinPeripheralAltStates();
//    portSensorsB.setPinPeripheralStates();
//
//}
//
//void runSens() {
//    //boolean result = reportDevicesWithAddressOn(&WireBackbone, 0x60, true);  // 0x10 is maybe finger position sensor.
//    reportDevicesOn(&WireBackbone,PRES_MODULE_ADDR, "Mainbus");
////  reportDevicesOn(&WireSensorA, TEMP_MODULE_ADDR, "Sensors Ax");
//    //reportDevicesOn(&WireSensorB,TEMP_MODULE_ADDR, "Sensors Bx");
//}
//
//void reportDevicesOn(TwoWire *wire, byte address, String label) {
//    byte error;
//
//    // The i2c_scanner uses the return value of
//    // the Write.endTransmisstion to see if
//    // a device did acknowledge to the address.
//
//    //wire->beginTransmission(address);
//    //error = wire->endTransmission();
//
//    if (reportDevicesWithAddressOn(wire, address)) {
//        digitalWrite(ledHb, HIGH);
//        if (address == PRES_MODULE_ADDR) {
//            readADC(wire, 1);
//        }
//    } else if (error == 4) {
//        Serial.print("Unknow error at address 0x");
//        if (address < 16)
//            Serial.print("0");
//        Serial.println(address, HEX);
//    }
//}
//
//void printDeviceName(int address) {
//    // Print recognized i2c device names:
//    if (address == 0x25) {
//        Serial.println("Sensirion SDP800-500Pa found...");
//    }
//    if (address == 0x26) {
//        Serial.println("Sensirion SDP800-501Pa found...");
//    }
//    if (address == 0x29) {
//        Serial.println("DLC-L01G-U2 or VL6180 found...");
//    }
//    if (address == 0x40) {
//        Serial.println("Sensirion SDP610-500Pa found...");
//    }
//    if (address == 0x50) {
//        Serial.println("FRAM/EEPROM found...");
//    }
//    if (address == 0x51) {
//        Serial.println("More memory found? Could be 1M FRAM.");
//    }
//    if (address == 0x7C) {
//        Serial.println("RESERVED...");
//    }
//}
//
//boolean reportDevicesWithAddressOn(TwoWire *wire, byte deviceAddress) {
//    wire->beginTransmission(deviceAddress);
//    byte error = wire->endTransmission();
//    boolean result = (error == 0);
//    return result;
//}
//
//boolean reportDevicesWithAddressOn(TwoWire *wire, byte deviceAddress, boolean report) {
//    wire->beginTransmission(deviceAddress);
//    byte error = wire->endTransmission();
//    boolean result = (error == 0);
//    char buffer[40];
//    if (report) {
//        if (result) {
//            sprintf(buffer, "Device was found on address 0x%02X", deviceAddress);
//        } else {
//            sprintf(buffer, "No device was found on address 0x%02X", deviceAddress);
//        }
//        Serial.println(buffer);
//    }
//    return result;
//}
//
//
//void readADC(TwoWire *wire, byte channel) {
//    // Configuration byte: 16-bit resolution, single-ended mode (channel), continuous conversion mode
//    byte configByte = B10000000 | (channel << 4);
//
//    wire->beginTransmission(PRES_MODULE_ADDR);
//    wire->write(configByte);
//    wire->endTransmission();
//
//    delay(100);  // Allow some time for conversion (adjust as needed)
//
//    wire->requestFrom(PRES_MODULE_ADDR, 3);  // Read 3 bytes from MCP3426
//    if (wire->available() >= 3) {
//        byte firstByte = wire->read();
//        byte secondByte = wire->read();
//        //byte thirdByte = wire->read();
//
//        // Combine the received bytes to form the 18-bit ADC value
//        int16_t rawValue = ((firstByte & 0x0F) << 8) | (secondByte);
//
//        // Print the ADC value for the specific channel
//        Serial.print("ADC Value (CH");
//        Serial.print(channel);
//        Serial.print("+): ");
//        Serial.println(rawValue);
//    }
//
//    //delay(1000);  // Delay before taking the next reading
//}
//
//void initI2C()
//{
//    Wire.begin(MODULE_ADDR);     // join i2c bus with address #4
//    Wire.onRequest(requestEvent);    // register event
//}
//
//// function that executes whenever data is received from master
//// this function is registered as an event, see setup()
//// Maybe useful for future usage
//
//// function that executes whenever data is requested by master
//// this function is registered as an event, see setup()
//
////int LL, int LA, int RA
//
//void requestEvent()
//{
//    readADC(reinterpret_cast<TwoWire *>(ADC), 1);
////    Wire.write(LLstatus);
////    Wire.write(LAstatus);
////    Wire.write(RAstatus);
//}
