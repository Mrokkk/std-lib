project(yacppl)
cmake_minimum_required(VERSION 3.0)

set(CPP_STANDARD c++1y)
set(DEBUG_LEVEL 3)
set(WARNING_FLAGS "-Wall -Wextra -Werror")

if(COVERAGE)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(COVERAGE_FLAGS "-O0 -fprofile-instr-generate -fcoverage-mapping")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov")
    else()
        set(COVERAGE_FLAGS "-O0 -fprofile-arcs -ftest-coverage")
    endif()
endif()

if(SANITIZERS)
    set(SANITIZERS_FLAGS "-fsanitize=address,undefined")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZERS_FLAGS}")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g${DEBUG_LEVEL} -std=${CPP_STANDARD} ${WARNING_FLAGS} ${COVERAGE_FLAGS} -fdiagnostics-color=always")

include_directories(include)

set(SOURCE_FILES
    tests/main.cpp
    tests/array.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_custom_target(tests-run
    DEPENDS ${PROJECT_NAME}
    COMMAND ./${PROJECT_NAME}
    COMMENT "Running tests")

if(COVERAGE)
    add_custom_target(clean-coverage
        COMMAND find ${CMAKE_BINARY_DIR} -name '*.gcda' -exec rm {} "\;"
        DEPENDS tests
        COMMENT "Cleaning coverage data")
    add_dependencies(tests-run clean-coverage)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_custom_target(tests-cov
            DEPENDS tests-run
            COMMAND LLVM_PROFILE_FILE=tests.profdata ./${PROJECT_NAME}
            COMMAND llvm-profdata merge -instr tests.profdata -o merged.profdata
            COMMAND llvm-cov report ./${PROJECT_NAME} -instr-profile=merged.profdata
            COMMENT "Running LLVM coverage generating")
    else()
        add_custom_target(tests-cov
            COMMAND gcovr -r ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}
            DEPENDS tests-run
            COMMENT "Running GCOVR coverage generating")
        add_custom_target(tests-cov-html
            COMMAND gcovr --html --html-details -o ut.coverage.html -r ${CMAKE_SOURCE_DIR}/include
            DEPENDS tests-run
            COMMENT "Running GCOVR coverage generating (HTML)")
    endif()
endif()

