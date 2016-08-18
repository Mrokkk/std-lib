cmake_minimum_required(VERSION 2.8)
project(std_lib)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CPP_STANDARD c++1y)
set(DEBUG_LEVEL 3)
set(WARNING_FLAGS "-Wall -Wextra")
set(COVERAGE_FLAGS "--coverage -fprofile-arcs -ftest-coverage")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g${DEBUG_LEVEL} -std=${CPP_STANDARD} ${WARNING_FLAGS} ${COVERAGE_FLAGS}")
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

if(COVERAGE)
    add_definitions("-g -O0 --coverage -fprofile-arcs -ftest-coverage -lgcov")
endif()

include_directories(googletest/googletest/include)
add_subdirectory(googletest/googletest)

set(SOURCE_FILES include/List.h include/Pointer.h include/Array.h tests/List.cpp tests/Array.cpp
        tests/SharedPointer.cpp tests/UniquePointer.cpp include/Move.h tests/String.cpp include/String.h
        include/initializer_list.h tests/Stack.cpp include/Stack.h include/Queue.h include/Exception.h tests/Queue.cpp
        tests/Mixed.cpp include/Algorithm.h)
include_directories(include)
add_executable(std_lib ${SOURCE_FILES})
target_link_libraries(std_lib gtest gtest_main pthread)
if(COVERAGE)
    ADD_CUSTOM_TARGET(coverage
        COMMAND gcovr -o ut.coverage.raw -r ../include . && gcovr --html --html-details -o ut.coverage.html -r ../include .
    )
endif()
