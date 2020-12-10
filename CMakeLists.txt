cmake_minimum_required(VERSION 3.19)
project(Matrix_chain_multiplication C)

set(CMAKE_C_STANDARD 99)

add_executable(Matrix_chain_multiplication main.c mat_util.h time_util.h defines.h)