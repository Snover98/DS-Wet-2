cmake_minimum_required(VERSION 3.7)
project(DS-Wet-2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        CompGlads.cpp
        CompGlads.h
        Gladiator.cpp
        Gladiator.h
        library1.h
        splayTree.h
        Trainer.h
        )
add_executable(DS-Wet-2 ${SOURCE_FILES})