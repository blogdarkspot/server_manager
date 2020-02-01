cmake_minimum_required (VERSION 3.12)

find_package (Boost 1.71.0 REQUIRED)

add_library(config OBJECT configuration.cpp)
add_library(tcp OBJECT tcp_server.cpp)
add_library(manager_servers OBJECT manager_servers.cpp)

add_executable(server)

target_include_directories(manager_servers PUBLIC ${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})
target_include_directories(config PUBLIC ${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})
target_include_directories(tcp PUBLIC ${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})

target_compile_features(manager_servers PUBLIC cxx_std_17)
target_compile_features(config PUBLIC cxx_std_17)
target_compile_features(tcp PUBLIC cxx_std_17)

target_sources(server PRIVATE main.cpp)

target_link_libraries(server config manager_servers tcp)