//
// Created by joris on 24-1-2024.
//

#include "I2C.h"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

sensorHubI2C::sensorHubI2C(const char* i2cDevice, int i2cAddr) : _i2cDevice(i2cDevice), _i2cAddr(i2cAddr), _i2cFile(-1) {}

sensorHubI2C::~sensorHubI2C()
{
    if (_i2cFile != -1) close(_i2cFile);
}

bool sensorHubI2C::begin()
{
    _i2cFile = open(_i2cDevice, O_RDWR);
    if (_i2cFile < 0)
    {
        return false;
    }

    if (ioctl(_i2cFile, I2C_SLAVE, _i2cAddr) < 0)
    {
        close(_i2cFile);
        return false;
    }

    return true;
}

bool sensorHubI2C::readData(char& red, char& black, char& white)
{
    unsigned char cmd[2] = {0x2C, 0x06};
    if (write(_i2cFile, cmd, 2) != 2)
    {
        return false;
    }
    usleep(10000);

    unsigned char data[3];
    if (read(_i2cFile, data, 3) != 3)
    {
        return false;
    }

    red = data[0];
    black = data[1];
    white = data[2];

    return true;
}
