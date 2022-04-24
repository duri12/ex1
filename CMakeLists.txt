cmake_minimum_required(VERSION 3.21)
project(mtm_ex1 C)

set(CMAKE_C_STANDARD 99)


add_executable(mtm_ex1 tool/main.c tool/AsciiArtTool.h tool/AsciiArtTool.c RLEList.c RLEList.h)
