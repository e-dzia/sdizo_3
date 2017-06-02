cmake_minimum_required(VERSION 3.7)
project(sdizo_3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Problem.cpp Problem.h DiscreteKnapsackProblem.cpp
        DiscreteKnapsackProblem.h TravellingSalesmanProblem.cpp TravellingSalesmanProblem.h
        Array3.cpp Array3.h Graph.h Graph.cpp GraphMatrix.cpp GraphMatrix.h)
add_executable(sdizo_3 ${SOURCE_FILES})