cmake_minimum_required(VERSION 3.23)

set(name BCIEvent)
set(BCI2000_DIR /opt/BCI2000)

project(${name})
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)


add_executable(${name}
    ../src/Main.cpp)

target_include_directories(${name} PUBLIC
    ../src
    ../src/blocks
    ../src/event
    ../src/builder
    ../src/variable
    ../src/state
    ../src/expression
    ../src/application)
    
target_include_directories(${name} PUBLIC
    ${BCI2000_DIR}/src/shared/modules/application
    ${BCI2000_DIR}/src/shared/gui
    ${BCI2000_DIR}/src/shared/utils
    ${BCI2000_DIR}/src/shared/utils/Lib
    ${BCI2000_DIR}/src/shared/types/
    ${BCI2000_DIR}/src/shared/accessors/
    ${BCI2000_DIR}/src/shared/config/
    ${BCI2000_DIR}/src/shared/bcistream/
    ${BCI2000_DIR}/src/shared/filters/
    ${BCI2000_DIR}/src/shared/state/
    ${BCI2000_DIR}/src/shared/modules/application/gui)
