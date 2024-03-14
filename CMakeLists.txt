cmake_minimum_required(VERSION 3.27)
project(Project_IAP C)

set(CMAKE_C_STANDARD 99)

add_executable(Project_IAP main.c
        board.c
        board.h
        player.h
        player.c)
