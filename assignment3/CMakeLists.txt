cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

project(assignment3)
add_executable(assignment3
        assignment3/main.cpp
        assignment3/concert.h
        assignment3/concert.cpp
        assignment3/seller.h
        assignment3/seller.cpp
        assignment3/customer.h
        assignment3/customer.cpp)
target_link_libraries(assignment3 pthread)
target_link_libraries(assignment3 m)

project(coen383)
