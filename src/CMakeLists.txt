cmake_minimum_required(VERSION 3.22)

# set the project name
project(blackscholes)

# specify C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify compiler flags
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -Werror -Wpedantic -Wunused -Wconversion -Wuninitialized -fanalyzer -lm")

# add the executable
add_executable(blackscholes main.cpp)

