cmake_minimum_required(VERSION 3.23.2)

set(NAME c_logger)
project(${NAME})

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} SHARED
	c_log.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER c_log.h)
