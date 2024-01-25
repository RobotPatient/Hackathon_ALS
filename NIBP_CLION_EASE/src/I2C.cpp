//
// Created by emiel on 25-1-2024.
//

#include <Wire.h>
#include "I2C.h"

void initI2C()
{
    Wire.begin(MODULE_ADDR);     // join i2c bus with address #4
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
    //bdshafhasd
//    Wire.write(LLstatus);
//    Wire.write(LAstatus);
//    Wire.write(RAstatus);
}
