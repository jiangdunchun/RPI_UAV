cmake_minimum_required (VERSION 2.8)

project (Demo)

# Locate libraries and headers
find_package(WiringPi REQUIRED)

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS}) 

aux_source_directory(. DIR_SRCS)

add_executable(Demo ${DIR_SRCS})
target_link_libraries(Demo ${WIRINGPI_LIBRARIES}) 