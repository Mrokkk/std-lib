project(yacppl)
cmake_minimum_required(VERSION 3.0)

if(NOT CPP_STD)
    set(CPP_STD c++1z)
endif()
message(STATUS "[CPP_STD] C++ standard: ${CPP_STD}")

option(COVERAGE "Generate coverage reports" OFF)
message(STATUS "[COVERAGE] Generate coverage reports: ${COVERAGE}")

option(SANITIZERS "Use asan and ubsan" OFF)
message(STATUS "[SANITIZERS] Use asan and ubsan: ${SANITIZERS}")

set(DEBUG_LEVEL 3)
set(WARNING_FLAGS "-Wall -Wextra -Werror")

add_subdirectory(tests)

