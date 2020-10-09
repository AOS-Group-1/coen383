cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

project(assignment1)
add_executable(assignment1
        assignment1/forktest.c)

project(assignment2)
add_executable(assignment2
        assignment2/main.c
        assignment2/job.h
        assignment2/job.c
        assignment2/run.h
        assignment2/run.c
        assignment2/FCFS_algorithm.h
        assignment2/FCFS_algorithm.c)
target_link_libraries(assignment2 m)
