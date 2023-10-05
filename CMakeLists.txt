cmake_minimum_required(VERSION 3.14)
project(data_stream_stats)
set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to Release as none was specified.")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
               "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_compile_options(-Wall -Wextra)

include_directories(include)
add_library(${PROJECT_NAME} STATIC
  src/data_stream_1d.cpp)


enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(${PROJECT_NAME}_test
  src/data_stream_1d_test.cpp
  src/main_test.cpp)
target_link_libraries(${PROJECT_NAME}_test gtest pthread ${PROJECT_NAME} ${GLOG_LIBRARIES})
