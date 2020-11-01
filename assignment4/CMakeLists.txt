cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

project(assignment4)
add_executable(assignment4
        main.cpp
        job.cpp
        job.h
        page.cpp
        page.h
        algorithms/FIFO.h
        algorithms/FIFO.cpp
        algorithms/LRU.h
        algorithms/LRU.cpp
        algorithms/LFU.h
        algorithms/LFU.cpp
        algorithms/MFU.h
        algorithms/MFU.cpp
        algorithms/random.h
        algorithms/random.cpp)

project(coen383)
