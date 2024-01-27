#ifndef SENSOR_H
#define SENSOR_H

#include <Wire.h>
#include <Arduino.h>

class Sensor {
  private:


  public:
    byte deviceAddress;
    TwoWire* wireObject;
    int16_t minWaarde;
    int16_t maxWaarde;
    //    TwoWire* P_wireObject;
    //    byte P_deviceAddress;

    Sensor(byte address, TwoWire* wire);
    Sensor(byte address, TwoWire* wire, int16_t inMinWaarde, int16_t inMaxWaarde);

    bool isConnected();
    byte isCableConnected(int16_t waarde);
    byte howCableConnected(byte waarde);
};

#endif  // SENSOR_H
