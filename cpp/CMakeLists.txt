cmake_minimum_required(VERSION 3.5)
project(bee)


set(CMAKE_C_FLAGS "-pthread -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 11)
set(LINK_DIR /usr/local/lib)
link_directories(${LINK_DIR})


add_executable(s0 s0.c)
add_executable(s1 s1.cc)
add_executable(s2 s2.cc)
add_executable(s3 s3.cc)
add_executable(s4 s4.cc)
add_executable(s5 s5.cc)
target_link_libraries(s5 gtest pthread)
add_executable(s6 s6.cc)
add_executable(s7 s7.cc)
add_executable(s9 s9.cc)
add_executable(s11 s11.cc)
target_link_libraries(s9 uv pthread)
