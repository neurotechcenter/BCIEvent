cmake_minimum_required(VERSION 3.23)

set(name BCIEvent)
set(bci2000_dir /opt/BCI2000)

project(${name})
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)



add_executable(${name}
    ../src/blocks/NormalBlock.cpp)

    target_include_directories(${name} PUBLIC
    ../src
    ../src/blocks
    ../src/event
    ../src/builder
    ../src/variable
    ${BCI2000_dir}/src/shared/application)
