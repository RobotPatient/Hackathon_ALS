//
// Created by Sudden on 1/24/2024.
//
#include <Arduino.h>
#include "readInfrared.h"

int LLstatus;
int LAstatus;
int RAstatus;

int LLVal;
int LAVal;
int RAVal;

 void initECG()
 {
     pinMode(SENSOR_LA, INPUT);
     pinMode(SENSOR_LL, INPUT);
     pinMode(SENSOR_RA, INPUT);
 }

 int readRawVal(int pin)
 {
     return analogRead(pin);
 }

void readValAndCheckConnection()
{
    LAVal =  readRawVal(SENSOR_LA);
    LLVal =  readRawVal(SENSOR_LL);
    RAVal =  readRawVal(SENSOR_RA);

    // Connection detection black lead.
    if (LAVal > 860) //black
    {
        LAstatus = 1;
    } else if (LAVal >= 700 && LAVal <= 860)
    {
        LAstatus = 0;
    } else
    {
        LAstatus = 2;
    }

    // Connection detection white lead.
    if (RAVal >= 550 && RAVal <= 700) //white
    {
        RAstatus= 1;
    } else if (RAVal >= 700 && RAVal <= 860)
    {
        RAstatus = 0;
    } else
    {
        RAstatus = 2;
    }

    // Connection detection red lead.
    if (LLVal <= 200) //red
    {
        LLstatus = 1;
    } else if (LLVal >= 720 && LLVal <= 780)
    {
        LLstatus = 0;
    } else
    {
        LLstatus = 2;
    }
}