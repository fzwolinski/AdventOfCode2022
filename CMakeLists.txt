cmake_minimum_required(VERSION 3.10)

project(AdventOfCode2022)

add_executable(day1 day1/day1.cpp)
configure_file(day1/input.txt day1_input.txt COPYONLY)
