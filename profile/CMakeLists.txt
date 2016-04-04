# file:   CMakeLists.txt
# author: Omar A Serrano
# date:   2016-04-03

cmake_minimum_required(VERSION 3.0.2)

project(ospp_profile)

add_executable(main profile_queue.cc)

get_filename_component(PARENT_DIR
  ${CMAKE_CURRENT_SOURCE_DIR} PATH)

target_include_directories(main PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PARENT_DIR})

target_compile_options(main PUBLIC -Wall -Wall -std=c++11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
