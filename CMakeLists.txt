cmake_minimum_required(VERSION 3.10)

project(AdventOfCode2022)

include_directories(helpers)

add_executable(day1 day1/day1.cpp)
configure_file(day1/input.txt day1_input.txt COPYONLY)

add_executable(day2 day2/day2.cpp)
configure_file(day2/input.txt day2_input.txt COPYONLY)
