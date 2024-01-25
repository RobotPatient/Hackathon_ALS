//
// Created by emiel on 25-1-2024.
//

#ifndef NIBP_CLION_EASE_ACTUATOR_HPP
#define NIBP_CLION_EASE_ACTUATOR_HPP

#define numActuators 6
// PA18 .. PA21
#define PA18 10
#define PA19 12
#define PA20 6
#define PA21 7
#define Act1 5
#define Act2 14

const int actuatorPins[numActuators] = {PA18, PA19, PA20, PA21, Act1, Act2};

void initActuators();
void actuatorBuzz();
void actuatorTrigger(int actuator, int durationON, int durationOFF);

#endif //NIBP_CLION_EASE_ACTUATOR_HPP
