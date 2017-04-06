cmake_minimum_required(VERSION 3.0.2)
include_directories(${ospp_SOURCE_DIR}/src)
include_directories(SYSTEM
  $ENV{GTEST_INC_DIR}
  $ENV{GMOCK_INC_DIR}
)
link_directories($ENV{GMOCK_LIB_DIR})
set(test_ospp_src test_queue.cc test_string.cc)
add_executable(test_ospp ${test_ospp_src})
target_link_libraries(test_ospp
  pthread
  gmock_main
)
