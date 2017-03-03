cmake_minimum_required(VERSION 2.8.9)
project (ci)

include_directories(include)

include_directories(/usr/include/check)
file(GLOB SOURCES "src/*.c")
add_executable(ci ${SOURCES})

target_link_libraries(ci check.so)
