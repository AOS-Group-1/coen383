cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

#project(assignment1)
#add_executable(assignment1
#        assignment1/forktest.c)
#
#project(assignment2)
#add_executable(assignment2
#        assignment2/main.c
#        assignment2/job.h
#        assignment2/job.c
#        assignment2/run.h
#        assignment2/run.c
#        assignment2/algorithms/FCFS_algorithm.h
#        assignment2/algorithms/FCFS_algorithm.c
#        assignment2/algorithms/SJF_algorithm.h
#        assignment2/algorithms/SJF_algorithm.c
#        assignment2/algorithms/SRT_algorithm.h
#        assignment2/algorithms/SRT_algorithm.c
#        assignment2/algorithms/priority_queue.h
#        assignment2/algorithms/priority_queue.c
#        assignment2/algorithms/RR_algorithm.h
#        assignment2/algorithms/RR_algorithm.c
#        assignment2/algorithms/HPF_NP_algorithm.h
#        assignment2/algorithms/HPF_NP_algorithm.c
#        assignment2/algorithms/HPF_P_algorithm.h
#        assignment2/algorithms/HPF_P_algorithm.c)
#target_link_libraries(assignment2 m)
#
#project(assignment2_rr)
#add_executable(assignment2_rr assignment2/round_robin.c)
#
#project(assignment2_hpf)
#add_executable(assignment2_hpf assignment2/hpf.c)

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
