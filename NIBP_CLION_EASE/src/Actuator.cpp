//
// Created by emiel on 25-1-2024.
//

#include <Arduino.h>
#include "Actuator.h"

void initActuators()
{
    for (int i = 0; i < numActuators; i++)
    {
        pinMode(actuatorPins[i], OUTPUT);
    }
}

void actuatorBuzz()
{
    for (int i = 0; i < numActuators; i++)
    {
        digitalWrite(actuatorPins[i], HIGH);
        delay(800);
        digitalWrite(actuatorPins[i], LOW);
        delay(500);
    }
}

void actuatorTrigger(int actuator, int durationON, int durationOFF)
{
    digitalWrite(actuatorPins[actuator],HIGH);
    delay(durationON);
    digitalWrite(actuatorPins[actuator], LOW);
    delay(durationOFF);
}
