//
// Created by Sudden on 1/24/2024.
//

#include <Wire.h>
#include "I2C.h"
#include "readInfrared.h"

void initI2C()
{
    Wire.begin(ECG_MODULE_ADDR);     // join i2c bus with address #4
    Wire.onRequest(requestEvent);    // register event
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
// Maybe useful for future usage

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()

//int LL, int LA, int RA

void requestEvent()
{

    Wire.write(LLstatus);
    Wire.write(LAstatus);
    Wire.write(RAstatus);
}