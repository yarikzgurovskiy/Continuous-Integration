cmake_minimum_required(VERSION 2.8.7)

#
# Common settings
#

# adds ./include to compiler include directories
include_directories(include)
# compiles code files from ./src folder
file(GLOB LIB_SOURCES "src/*.c")

#
# first project (static lib)
#
project (ci)
# to build static library target with name libmtmodule.a
add_library(${CMAKE_PROJECT_NAME} STATIC ${LIB_SOURCES})

# to install library headers
install(
    DIRECTORY include/ DESTINATION /usr/local/include
    FILES_MATCHING PATTERN "*.h"
)
# Set the location for library installation
# Use "sudo make install" in build directory to apply
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION /usr/local/lib)

#
# Test project
#
project(a.out)
add_executable(${CMAKE_PROJECT_NAME} "tests/main.c" ${LIB_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} libcheck.so)

#
# Create make test
#
enable_testing()
add_test(unit-tests ${CMAKE_PROJECT_NAME})

## Coverage
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)
include(CodeCoverage)
setup_target_for_coverage(${CMAKE_PROJECT_NAME}_coverage ${CMAKE_PROJECT_NAME} coverage)
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")