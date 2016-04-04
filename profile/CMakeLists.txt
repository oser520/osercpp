# file:   CMakeLists.txt
# author: Omar A Serrano
# date:   2016-04-03

cmake_minimum_required(VERSION 3.0.2)

project(ospp_profile)

add_executable(profile_queue profile_queue.cc)

target_include_directories(main PUBLIC . ..)
target_compile_options(main PUBLIC -Wall -Wall -std=c++11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
