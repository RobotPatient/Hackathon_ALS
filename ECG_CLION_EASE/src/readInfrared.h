//
// Created by Sudden on 1/24/2024.
//

#ifndef ECG_CLION_EASE_READINFRARED_H
#define ECG_CLION_EASE_READINFRARED_H

// Sensor Definitions:
#define SENSOR_LL A1  // PB08 red
#define SENSOR_LA A2  // PB09 black
#define SENSOR_RA A3  // PA04 white

// Variables:
extern int LLVal;
extern int LAVal;
extern int RAVal;

extern int LLstatus; // 0 , 1 , 2 values. 0 is not connected; 1 is connected ; 2 is wrongly connected
extern int LAstatus;
extern int RAstatus;

// Functions:
void initECG();
void readValAndCheckConnection();
int readRawVal(int pin);

#endif //ECG_CLION_EASE_READINFRARED_H
