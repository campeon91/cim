cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -pedantic")

project(cim VERSION 0.1 LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(
    cim
    src/main.cpp
    )