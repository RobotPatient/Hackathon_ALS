/*
    Johan Korten
    for HAN ESE, WKZ, Cap Gemini Hackaton 2024

    V1.0 Jan 2024

    Based on Wire Slave Sender and Receiver by Nicholas Zambetti <http://www.zambetti.com> March 2006

*/
#include <Arduino.h>
#include "HeartBeat.h"
#include "readInfrared.h"
#include "I2C.h"

#define HEARTBEAT_LEDPIN 14
#define DEFAULT_HEARTBEAT_INTERVAL 1000

HeartBeat heartBeat = HeartBeat(); // (HEARTBEAT_LEDPIN, DEFAULT_HEARTBEAT_INTERVAL) ;

void setup() {
    Serial.begin(9600);
    Serial.print("working");
    heartBeat.begin();
    initI2C();
    initECG();
}

void loop() {
    heartBeat.blink();
    readValAndCheckConnection();
    Serial.write(LLstatus);
    Serial.write(RAstatus);
    Serial.write(LAstatus);
    delay(100);
}