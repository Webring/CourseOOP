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
        MixDistribution/MixDistribution.tpp
        MixDistribution/MixDistribution.h
        EmpiricDistribution/EmpiricDistribution.cpp
        EmpiricDistribution/EmpiricDistribution.h
        interfaces.h
        Estimate/Estimate.cpp
        Estimate/Estimate.h
        Plotter/Plotter.cpp
)
