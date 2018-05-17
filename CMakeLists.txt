cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(pulsar VERSION 0.1 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} \
    -O2 \
    -Wall \
    -pedantic \
    -pthread")

set(PULSAR_SOURCES
    src/main.cpp
    src/SerialHandler.h
    src/SerialHandler.cpp
    src/ComManager.h
    src/ComManager.cpp)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(
        format
        COMMAND
            clang-format-5.0 -style=Chromium -i ${PULSAR_SOURCES}
        WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})
endif()

add_executable(pulsar ${PULSAR_SOURCES})