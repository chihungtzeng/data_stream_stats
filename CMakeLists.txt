cmake_minimum_required(VERSION 3.14)
project(data_stream_stats)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to Release as none was specified.")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
               "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_compile_options(-Wall -Wextra)

include_directories(include)
add_library(${PROJECT_NAME} STATIC
  src/data_stream_1d.cpp
  src/data_stream_2d.cpp
  src/indexed_priority_queue.cpp
  src/median_tracker.cpp
  )


enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(${PROJECT_NAME}_test
  src/data_stream_1d_test.cpp
  src/data_stream_2d_test.cpp
  src/indexed_priority_queue_test.cpp
  src/median_tracker_test.cpp
  src/main_test.cpp)
target_link_libraries(${PROJECT_NAME}_test gtest pthread ${PROJECT_NAME})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-fsanitize=fuzzer,address,undefined)
	add_link_options(-fsanitize=fuzzer,address,undefined -fPIE)

	add_executable(data_stream_fuzz_test src/data_stream_fuzz_test.cpp)
	target_link_libraries(data_stream_fuzz_test pthread ${PROJECT_NAME})
endif()
