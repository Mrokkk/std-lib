project(yacppl)
cmake_minimum_required(VERSION 3.0)

set(CPP_STANDARD c++1y)
set(DEBUG_LEVEL 3)
set(WARNING_FLAGS "-Wall -Wextra -Werror")

add_subdirectory(tests)

