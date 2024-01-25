#ifndef SENSOR_H
#define SENSOR_H

#include <Wire.h>
#include <Arduino.h>

class Sensor {
  private:


  public:
    byte deviceAddress;
    TwoWire* wireObject;
    //    TwoWire* P_wireObject;
    //    byte P_deviceAddress;

    Sensor(byte address, TwoWire* wire);
    bool isConnected();
};

#endif  // SENSOR_H
