cmake_minimum_required(VERSION 3.15)
project(OMDB C)

set(CMAKE_C_STANDARD 99)

add_executable(OMDB main.c film.h film.c moviedatabase.c moviedatabase.h)