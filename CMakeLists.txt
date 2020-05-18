# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required(VERSION 3.8)

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

set(CMAKE_BUILD_TYPE "Debug")


if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )
message(STATUS "Build Type:${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS}")

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(GAPING_SECURITY_HOLE "nc with -e option" ON)
option(TELNET "nc with -t option" ON)


# set the project name
project(lcx  VERSION 1.0)

set (LCX_VERSION_MAJOR 0)
set (LCX_VERSION_MINOR 1)
set (LCX_VERSION "1.0")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/LcxConfig.h.in"
  "${PROJECT_BINARY_DIR}/LcxConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

file(GLOB LCX_SOURCES src/*.c)
file(GLOB_RECURSE LIB_SOURCES lib/*.c)
file(GLOB_RECURSE LCX_HEADERS src/*.h lib/*.h)

set (LCX_INCLUDE_DIRS "")
foreach (_headerFile ${LCX_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND LCX_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES LCX_INCLUDE_DIRS)

MESSAGE(STATUS "LCX_INCLUDE_DIRS is ${LCX_INCLUDE_DIRS}")
MESSAGE(STATUS "LCX_SOURCES is ${LCX_SOURCES}")

# librarys
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# add the executable
add_executable (lcx ${LCX_SOURCES} ${LIB_SOURCES})
target_include_directories(lcx PRIVATE ${LCX_INCLUDE_DIRS})
target_link_libraries (lcx Threads::Threads)