cmake_minimum_required(VERSION 3.23)

set(name BCIEvent)


project(${name})
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_library(${name}
    ../src/blocks/NormalBlock.cpp)

    target_include_directories(${name} PUBLIC
    ../src
    ../src/blocks
    ../src/event)
