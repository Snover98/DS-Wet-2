cmake_minimum_required(VERSION 3.7)
project(DS-Wet-2)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        mainSys.cpp
        #main3.cpp
        #main2.cpp
        linkedList.h
        Coliseum.h
        Coliseum.cpp
        DSFunctions.cpp
        Exceptions.h
        Gladiator.h
        Gladiator.cpp
        CompGlads.h
        CompGlads.cpp
        library1.h
        splayTree.h
        Trainer.h
        Trainer.cpp
        binTree.h
        genericFunction.h
        TreeNode.h
        genericFunction.h
        TreeNode.h
        )
add_executable(DS-Wet-2 ${SOURCE_FILES})
