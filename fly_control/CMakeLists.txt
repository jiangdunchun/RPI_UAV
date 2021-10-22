cmake_minimum_required (VERSION 2.8)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

project (fly_control)

find_package(WiringPi REQUIRED)
set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "-pthread" LINK_FLAGS "-pthread")

include_directories(${WIRINGPI_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party)

file(GLOB_RECURSE CPP_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${CPP_SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${WIRINGPI_LIBRARIES} pthread) 