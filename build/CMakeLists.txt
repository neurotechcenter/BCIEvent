cmake_minimum_required(VERSION 3.23)

set(BCI2000_DIR /opt/BCI2000/)

include(sources.cmake)
include(LibTiny.cmake)

set(name BCIEventApplication)

project(${name})
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})


if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-include gccprefix.h)
endif()


list(TRANSFORM SOURCES_BCI PREPEND ${BCI2000_DIR})
list(TRANSFORM INCLUDE_BCI PREPEND ${BCI2000_DIR})

add_executable(${name}
    ../src/application/main.cpp ${SOURCES_CPP} ${SOURCES_BCI} ${SRC_LIBTINY})

target_compile_definitions(${name} PUBLIC USE_QT)

target_include_directories(${name} PUBLIC
    ../src
    ../src/blocks
    ../src/event
    ../src/builder
    ../src/variable
    ../src/state
    ../src/expression
    ../src/application
    )
target_include_directories(${name} PUBLIC ${INCLUDE_BCI})

set(QT_MODULES Core Widgets Gui)

if(NOT WIN32 AND NOT APPLE)
    list(APPEND QT_MODULES X11Extras)
endif()

set(QT_MODULE_NAMES ${QT_MODULES})
list(TRANSFORM QT_MODULE_NAMES PREPEND Qt5::)

find_package(Qt5 COMPONENTS ${QT_MODULES} REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PortAudio REQUIRED)

message(${OPENGL_LIBRARIES})

target_link_libraries(${name} PUBLIC ${QT_MODULE_NAMES} ${OPENGL_LIBRARIES} ${PORTAUDIO_LIBRARIES})
