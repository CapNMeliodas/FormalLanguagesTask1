cmake_minimum_required(VERSION 3.4)

set(PROJECT_NAME project1)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/nier_automata.cpp)

add_library(project1_lib ${SRC_FILES})
add_executable(project1 ${PROJECT_SOURCE_DIR}/src/nier_automata.cpp)

target_link_libraries(project1 project1_lib)

#Testing
option(BUILD_TESTS "Build all tests." OFF)

if (BUILD_TESTS)
	add_subdirectory(ext/gtest-1.8.0)
	enable_testing()

	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  	add_executable(runUnitTests ${TEST_SRC_FILES})

  	target_link_libraries(runUnitTests gtest gtest_main)

  	target_link_libraries(runUnitTests project1_lib)

  	add_test(UnitTests runUnitTests)

endif()