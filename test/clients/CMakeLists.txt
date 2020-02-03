
find_package (Boost 1.71.0 REQUIRED)

add_executable(tcp_client)

target_include_directories(tcp_client PRIVATE ${Boost_INCLUDE_DIRS})

target_sources(tcp_client PRIVATE tcp_client.cpp)

