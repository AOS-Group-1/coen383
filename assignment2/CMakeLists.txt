cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

project(assignment2)
add_executable(assignment2
        main.c
        job.h
        job.c
        run.h
        run.c
        algorithms/FCFS_algorithm.h
        algorithms/FCFS_algorithm.c
        algorithms/SJF_algorithm.h
        algorithms/SJF_algorithm.c
        algorithms/SRT_algorithm.h
        algorithms/SRT_algorithm.c
        algorithms/priority_queue.h
        algorithms/priority_queue.c
        algorithms/RR_algorithm.h
        algorithms/RR_algorithm.c
        algorithms/HPF_NP_algorithm.h
        algorithms/HPF_NP_algorithm.c
        algorithms/HPF_P_algorithm.h
        algorithms/HPF_P_algorithm.c)
target_link_libraries(assignment2 m)

project(assignment2_rr)
add_executable(assignment2_rr round_robin.c)

project(assignment2_hpf)
add_executable(assignment2_hpf hpf.c)
