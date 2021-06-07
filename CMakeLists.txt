cmake_minimum_required(VERSION 3.10)
project(netmock C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(
        netmock SHARED
        env.c netmock.c
        env.h netmock.h
)
target_link_libraries(netmock dl)
install(TARGETS netmock)
