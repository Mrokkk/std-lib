include(cmake-utils/utils.cmake)
include(cmake-utils/coverage.cmake)
include(cmake-utils/sanitizers.cmake)

if(COVERAGE)
    add_coverage_flags()
endif()

if(SANITIZERS)
    add_sanitizers_flags()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g${DEBUG_LEVEL} -std=${CPP_STD} ${WARNING_FLAGS} -fdiagnostics-color=always")

include_directories(${CMAKE_SOURCE_DIR}/include)

if(NOT CI)
    set(TESTS_PARAMS "--oneliners")
endif()

add_executable(${PROJECT_NAME}
    main.cpp
    array.cpp
    inherited_list.cpp
    kernel_list.cpp
    list.cpp
    mixed.cpp
    optional.cpp
    queue.cpp
    shared_ptr.cpp
    stack.cpp
    unique_ptr.cpp
    range.cpp
    allocator.cpp
    path.cpp
    string.cpp
    hash_map.cpp
)

add_run_target(${PROJECT_NAME} tests-run)

if(NOT SANITIZERS)
    add_valgrind_target(${PROJECT_NAME} tests-valgrind)
endif()

if(COVERAGE)
    add_coverage_targets(${PROJECT_NAME} tests-run tests ${CMAKE_SOURCE_DIR}/include)
endif()

