cmake_minimum_required(VERSION 3.12)
project(CHPS0711_2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER "mpicc")
set(CMAKE_C_FLAGS "-pipe -Wall -Wextra -pedantic -O3")

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

add_executable(CHPS0711_2 Eratosthene.c)