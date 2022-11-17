cmake_minimum_required(VERSION 3.20)
project(runnable)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
        main.cpp
        calculate/Distance.cpp
        calculate/Distance.h
        calculate/Euclidean.h
        calculate/Euclidean.cpp
        calculate/Minkowski.h
        calculate/Minkowski.cpp
        calculate/Canberra.h
        calculate/Canberra.cpp
        calculate/Chebyshev.cpp
        calculate/Chebyshev.h
        calculate/Manhattan.cpp
        calculate/Manhattan.h)
