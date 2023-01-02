cmake_minimum_required(VERSION 3.10)

project(AdventOfCode2022)

include_directories(helpers)

add_executable(day1 day1/day1.cpp)
configure_file(day1/input.txt day1_input.txt COPYONLY)

add_executable(day2 day2/day2.cpp)
configure_file(day2/input.txt day2_input.txt COPYONLY)

add_executable(day3 day3/day3.cpp)
configure_file(day3/input.txt day3_input.txt COPYONLY)

add_executable(day4 day4/day4.cpp)
configure_file(day4/input.txt day4_input.txt COPYONLY)

add_executable(day5 day5/day5.cpp)
configure_file(day5/input.txt day5_input.txt COPYONLY)

add_executable(day6 day6/day6.cpp)
configure_file(day6/input.txt day6_input.txt COPYONLY)

add_executable(day7 day7/day7.cpp)
configure_file(day7/input.txt day7_input.txt COPYONLY)

add_executable(day8 day8/day8.cpp)
configure_file(day8/input.txt day8_input.txt COPYONLY)
