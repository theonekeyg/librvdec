cmake_minimum_required(VERSION 3.14)
project(librvdec)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(BUILD_TESTING "Enable test builds" ON)

set(rvdec_build_include_dirs
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/include
)
include_directories(${rvdec_build_include_dirs})

add_subdirectory(src)

if(BUILD_TESTING)
  include(CTest)
  add_subdirectory(test EXCLUDE_FROM_ALL)
endif()
