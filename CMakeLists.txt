cmake_minimum_required(VERSION 2.8)
project(std_lib)

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

set(SOURCE_FILES include/list.h include/pointer.h include/array.h tests/list.cpp tests/array.cpp
        tests/shared_ptr.cpp tests/unique_ptr.cpp include/move.h tests/String.cpp include/String.h
        include/initializer_list.h tests/stack.cpp include/stack.h include/queue.h tests/queue.cpp
        tests/mixed.cpp include/algorithm.h)
include_directories(include)
add_executable(std_lib ${SOURCE_FILES})
target_link_libraries(std_lib gtest gtest_main pthread)
if(COVERAGE)
    ADD_CUSTOM_TARGET(coverage
        COMMAND gcovr -o ut.coverage.raw -r ../include . && gcovr --html --html-details -o ut.coverage.html -r ../include . && cat ut.coverage.raw
    )
endif()

add_custom_target(tests-run DEPENDS ${PROJECT_NAME} COMMAND ./${PROJECT_NAME})

