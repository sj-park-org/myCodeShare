cmake_minimum_required(VERSION 3.29.6)
project(code1 C)

set(CMAKE_C_STANDARD 11)

add_executable(code1 main2.c
        SimpleList2.h
        SimpleList2.c)

#add_executable(code1 main.c
#        SimpleList.h
#        SimpleList.c
#)