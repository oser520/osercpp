# file:   CMakeLists.txt
# author: Omar A Serrano
# date:   2016-04-03

cmake_minimum_required(VERSION 3.0.2)

project(ospp_profile CXX)

add_executable(main profile_queue.cc)

get_filename_component(PARENT_DIR
  ${CMAKE_SOURCE_DIR} PATH)

target_include_directories(main PUBLIC
  ${CMAKE_SOURCE_DIR} ${PARENT_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_MODULE_PATH ${PARENT_DIR}/cmake)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_cov main coverage)
    target_compile_options(main PUBLIC -std=c++11)
endif()
