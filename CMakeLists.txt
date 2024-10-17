cmake_minimum_required(VERSION 3.27)
project(oop)

set(CMAKE_CXX_STANDARD 17)

add_executable(oop
        menu.cpp
        main.cpp
        menu.cpp
        menu.h
        math.cpp
        math.h
        consts.h
        utils.h
        GeneralDistribution/GeneralDistribution.cpp
        GeneralDistribution/GeneralDistribution.h
        test.cpp
        test.h
)
