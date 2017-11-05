cmake_minimum_required(VERSION 3.8)
project(WhoseExcavatorTechnologyAdvanced)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Vector.h Test.cpp Test.h BasicString.h)
add_executable(WhoseExcavatorTechnologyAdvanced ${SOURCE_FILES})