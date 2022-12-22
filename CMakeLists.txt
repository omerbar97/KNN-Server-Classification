cmake_minimum_required(VERSION 2.8.12.2)
project(a.out)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(client.out
        main.cpp
        calculate/Distance/Distance.cpp
        calculate/Distance/Distance.h
        calculate/Distance/Euclidean.h
        calculate/Distance/Euclidean.cpp
        calculate/Distance/Minkowski.h
        calculate/Distance/Minkowski.cpp
        calculate/Distance/Canberra.h
        calculate/Distance/Canberra.cpp
        calculate/Distance/Chebyshev.cpp
        calculate/Distance/Chebyshev.h
        calculate/Distance/Manhattan.cpp
        calculate/Distance/Manhattan.h
        calculate/ReadCSV.cpp
        calculate/ReadCSV.h
        calculate/Algorithim/Select.cpp
        calculate/Algorithim/Select.h
        calculate/Algorithim/Knn.h
        calculate/Algorithim/Knn.cpp
        calculate/Algorithim/CSVStruct.h
        calculate/input.cpp
        calculate/input.h)

add_executable(server.out
        calculate/Distance/Distance.cpp
        calculate/Distance/Distance.h
        calculate/Distance/Euclidean.h
        calculate/Distance/Euclidean.cpp
        calculate/Distance/Minkowski.h
        calculate/Distance/Minkowski.cpp
        calculate/Distance/Canberra.h
        calculate/Distance/Canberra.cpp
        calculate/Distance/Chebyshev.cpp
        calculate/Distance/Chebyshev.h
        calculate/Distance/Manhattan.cpp
        calculate/Distance/Manhattan.h
        calculate/ReadCSV.cpp
        calculate/ReadCSV.h
        calculate/Algorithim/Select.cpp
        calculate/Algorithim/Select.h
        calculate/Algorithim/Knn.h
        calculate/Algorithim/Knn.cpp
        calculate/Algorithim/CSVStruct.h
        calculate/input.cpp
        calculate/input.h
        server/Server.cpp
        server/Server.h
        server/serverMain.cpp)