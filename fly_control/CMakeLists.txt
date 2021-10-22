cmake_minimum_required (VERSION 2.8)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

project (Demo)

# Locate libraries and headers
find_package(WiringPi REQUIRED)

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS}) 

file(GLOB_RECURSE CPP_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_executable(Demo main.cpp common/logger.cpp device/motor.cpp device/mpu6050.cpp device/remote_control.cpp)
target_link_libraries(Demo ${WIRINGPI_LIBRARIES}) 