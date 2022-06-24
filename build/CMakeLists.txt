cmake_minimum_required(VERSION 3.23)

set(name BCIEvent)


project(${name})
include_directories(../src)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_library(BCIEvent
	../src/blocks/block.cpp)
