//
// Created by joris on 24-1-2024.
//
#include <iostream>
#include "I2C/I2C.h"

char leadRed, leadBlack, leadWhite;

int main() {
    while(true) {

        //create new instance
        sensorHubI2C shi;

        //start I2C connection
        if (!shi.begin()) {
            std::cerr << "Failed to initialize I2C";
            return 1;
        }

        if (shi.readData(leadRed, leadBlack, leadWhite)) {

            int lr = (int)leadRed;
            int lb = (int)leadBlack;
            int lw = (int)leadWhite;
//        if (leadRed == true) {
//            std::cout << "The red lead is connected" << std::endl;
//        } else std::cout << "The red lead is NOT connected" << std::endl;
//
//        if (leadRed == true) {
//            std::cout << "The black lead is connected" << std::endl;
//        } else std::cout << "The red lead is NOT connected" << std::endl;
//
//        if (leadRed == true) {
//            std::cout << "The white lead is connected" << std::endl;
//        } else std::cout << "The red lead is NOT connected" << std::endl;
            std::cout << "char 1: " << lr << std::endl;
            std::cout << "char 2: " << lb << std::endl;
            std::cout << "char 3: " << lw << std::endl;
        } else {
            std::cerr << "failed to read data from the I2C bus" << std::endl;
            return 1;
        }
    }

    return 0;
}
