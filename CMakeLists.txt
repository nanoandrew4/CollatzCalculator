cmake_minimum_required(VERSION 3.9)
project(Collatz)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-Ofast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Collatz main.cpp)

target_link_libraries(Collatz gmp)