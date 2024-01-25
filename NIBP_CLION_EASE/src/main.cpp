//
// Created by emiel on 25-1-2024.
//

#include <Arduino.h>
#include "HeartBeat.h"
#include "Actuator.h"
#include "I2C.h"

#define HEARTBEAT_LEDPIN 14
#define DEFAULT_HEARTBEAT_INTERVAL 1000

HeartBeat heartBeat = HeartBeat(); // (HEARTBEAT_LEDPIN, DEFAULT_HEARTBEAT_INTERVAL) ;

// the setup function runs once when you press reset or power the board
void setup() {
    heartBeat.begin();
    initActuators();
    initI2C();
    actuatorBuzz();
}

// the loop function runs over and over again forever
void loop() {
    heartBeat.blink();
}