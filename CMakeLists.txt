cmake_minimum_required(VERSION 3.14)
project(riscv_decoder)

set(CMAKE_CXX_STANDARD 17)
option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(BUILD_TESTING "Enable test builds" ON)
include_directories(src/include)

add_subdirectory(src)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()
