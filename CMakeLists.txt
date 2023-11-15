cmake_minimum_required(VERSION 3.26)
project(Vole_Machine)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Vole_Machine
        CPU.cpp
        CPU.h
        Machine.cpp
        Machine.h
        Main.cpp
        Memory.cpp
        Memory.h)
