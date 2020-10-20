cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

project(assignment3)
add_executable(assignment3
        main.cpp
        concert.h
        concert.cpp
        seller.h
        seller.cpp
        customer.h
        customer.cpp)
target_link_libraries(assignment3 pthread)
target_link_libraries(assignment3 m)

project(coen383)
