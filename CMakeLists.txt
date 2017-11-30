cmake_minimum_required(VERSION 3.7)
project(DS-Wet-2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Gladiator.h
        Gladiator.cpp
        CompGlads.h
        CompGlads.cpp
        library1.h
        splayTree.h
        Trainer.h
        binTree.h
        )
add_executable(DS-Wet-2 ${SOURCE_FILES})
