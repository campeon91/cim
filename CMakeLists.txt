cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++14 -Wall -pedantic")

project(cim VERSION 0.1 LANGUAGES CXX)

add_executable(
    cim
    src/main.cpp
    src/SerialHandler.cpp
    src/ComManager.cpp
    )