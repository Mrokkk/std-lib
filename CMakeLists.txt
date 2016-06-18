cmake_minimum_required(VERSION 3.5)
project(std_lib)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
include(Coverage)

set(CMAKE_C_COMPILER "gcc-6.1")
set(CMAKE_CXX_COMPILER "g++-6.1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O0 -std=c++14 -lboost_unit_test_framework --coverage -fprofile-arcs -ftest-coverage -Wall")
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

include_directories(include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

setup_target_for_coverage(${PROJECT_NAME}_coverage ${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/coverage)

set(SOURCE_FILES include/List.h include/Pointer.h include/Array.h tests/List.cpp tests/Array.cpp
        tests/SharedPointer.cpp tests/UniquePointer.cpp include/Move.h tests/String.cpp include/String.h
        include/initializer_list.h tests/Stack.cpp include/Stack.h include/Queue.h include/Exception.h tests/Queue.cpp
        tests/Mixed.cpp include/Algorithm.h)

add_executable(std_lib ${SOURCE_FILES})
target_link_libraries(std_lib gtest gtest_main pthread)
