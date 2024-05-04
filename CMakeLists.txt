cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_C_COMPILER "C:/TDM-GCC-64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/TDM-GCC-64/bin/g++.exe")

set(PROJECT_NAME GreedySnake)
project(${PROJECT_NAME} C CXX)

set(PROJECT_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_ROOT_PATH}/bin/)

include_directories(${PROJECT_ROOT_PATH}/include)
include_directories(${PROJECT_ROOT_PATH}/include/thirdpart)

link_directories(${PROJECT_ROOT_PATH}/lib)

ADD_SUBDIRECTORY(src)
