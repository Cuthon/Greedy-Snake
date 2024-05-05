cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT_NAME GreedySnake)
project(${PROJECT_NAME} C CXX)

set(PROJECT_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_ROOT_PATH}/bin/)

include_directories(${PROJECT_ROOT_PATH}/include)
include_directories(${PROJECT_ROOT_PATH}/include/thirdpart)

link_directories(${PROJECT_ROOT_PATH}/lib)
link_directories(C:/TDM-GCC-64/x86_64-w64-mingw32/lib)

ADD_SUBDIRECTORY(src)
