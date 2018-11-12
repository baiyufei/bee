cmake_minimum_required(VERSION 3.5)
project(simulate)
set(CMAKE_CXX_STANDARD 11)
add_executable(simulate simulate.cc TDOA.cc)
