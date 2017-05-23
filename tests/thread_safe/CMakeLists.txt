include(../cmake-utils/utils.cmake)
include(../cmake-utils/sanitizers.cmake)

add_sanitizers_flags()

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/tests/yatf/include)

find_package(Threads REQUIRED)
add_executable(${PROJECT_NAME}-thread_safe main.cpp shared_ptr.cpp)
target_link_libraries(${PROJECT_NAME}-thread_safe "${CMAKE_THREAD_LIBS_INIT}")
add_run_target(${PROJECT_NAME}-thread_safe tests-thread_safe-run)
