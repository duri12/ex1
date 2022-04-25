cmake_minimum_required(VERSION 3.21)
project(mtm_ex1 C)

set(CMAKE_C_STANDARD 99)


add_executable(mtm_ex1  RLEList.c RLEList.h tool/main_for_testing.c)
