project(I2Ctest)
add_executable(I2C main.cpp I2C/I2C.cpp)
target_include_directories(I2C PUBLIC I2C)