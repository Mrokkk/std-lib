cmake_minimum_required(VERSION 2.8)
project(yacppl)

set(CPP_STANDARD c++1y)
set(DEBUG_LEVEL 3)
set(WARNING_FLAGS "-Wall -Wextra -Werror")
set(COVERAGE_FLAGS "--coverage -fprofile-arcs -ftest-coverage")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g${DEBUG_LEVEL} -std=${CPP_STANDARD} ${WARNING_FLAGS} -fdiagnostics-color=always -D_GLIBCXX_USE_CXX11_ABI=0")

if(COVERAGE)
    add_definitions("-O0 -fprofile-arcs -ftest-coverage")
endif()

include_directories(include)
include_directories(googletest/googletest/include)
add_subdirectory(googletest/googletest)

set(SOURCE_FILES
    tests/list.cpp
    tests/array.cpp
    tests/shared_ptr.cpp
    tests/unique_ptr.cpp
    tests/stack.cpp
    tests/queue.cpp
    tests/mixed.cpp
    tests/af_list.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} gtest gtest_main pthread)

add_custom_target(tests-run DEPENDS ${PROJECT_NAME} COMMAND ./${PROJECT_NAME} --gtest_color=yes)

if(COVERAGE)
    target_link_libraries(${PROJECT_NAME} gcov)
    add_custom_target(tests-cov
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}
        DEPENDS tests-run
    )
    add_custom_target(tests-cov-html
        COMMAND gcovr --html --html-details -o ut.coverage.html -r ${CMAKE_SOURCE_DIR}/include
        DEPENDS tests-run
    )
endif()

