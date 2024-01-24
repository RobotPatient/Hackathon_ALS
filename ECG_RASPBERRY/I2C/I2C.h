//
// Created by joris on 24-1-2024.
//

#ifndef I2C_H
#define I2C_H

#include <cstdint>

class sensorHubI2C
{
public:
    sensorHubI2C(const char* i2cDevice = "/dev/i2c-1", int i2cAddr = 0x44);
    ~sensorHubI2C();

    bool begin();
    bool readData(char&, char&, char&);

private:
    const char* _i2cDevice;
    int _i2cAddr;
    int _i2cFile;
};

#endif
