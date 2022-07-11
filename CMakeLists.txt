include(sources.cmake)


if(CMAKE_CXX_STANDARD LESS 20)
	message( FATAL_ERROR "C++ standard must be 20 or later" )
endif()

if( NOT BCIEVENT_APP_NAME )
	message("BCIEVENT_APP_NAME not set; using default name BCIEventApplication")
	set(BCIEVENT_APP_NAME BCIEventApplication)
endif()

message("Adding BCIEvent Application ${BCIEVENT_APP_NAME}")
list(TRANSFORM INCLUDE_EVENT PREPEND ${PROJECT_SOURCE_DIR}/../src/custom/BCIEvent/)
list(TRANSFORM SOURCES_EVENT PREPEND ${PROJECT_SOURCE_DIR}/../src/custom/BCIEvent/)

bci2000_add_application_module(
  ${BCIEVENT_APP_NAME}
  ${SOURCES_EVENT}
)

add_compile_definitions(BCIEVENT_APP_NAME=${BCIEVENT_APP_NAME})
target_include_directories(${BCIEVENT_APP_NAME} PUBLIC ${INCLUDE_EVENT})
