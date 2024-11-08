cmake_minimum_required(VERSION 3.10)

project(tiny_plus_scanner)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(tiny_plus_scanner 
    src/main.c
    src/scan.c
    src/util.c
)