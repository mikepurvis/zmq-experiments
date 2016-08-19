cmake_minimum_required(VERSION 2.8.12)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(libzmq REQUIRED)

project(exp)

include_directories(${LIBZMQ_INCLUDE_DIRS})
add_executable(test_udp test_udp.cpp)
target_link_libraries(test_udp ${LIBZMQ_LIBRARIES})
