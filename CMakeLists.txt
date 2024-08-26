cmake_minimum_required(VERSION 3.23.2)

set(NAME c-logger)
project(${NAME})

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} SHARED
	clog.c
)

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
	target_compile_definitions(c-logger PUBLIC DEBUG=ON)
endif()
target_compile_definitions(c-logger PUBLIC LOG_SYNC=ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER clog.h)
