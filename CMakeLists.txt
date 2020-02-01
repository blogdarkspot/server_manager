cmake_minimum_required(VERSION 3.12)

project (Server)

set (TEST OFF)
add_subdirectory(src)

if(TEST)
    enable_testing()
    add_subdirectory(test)
endif()