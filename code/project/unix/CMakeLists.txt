cmake_minimum_required(VERSION 3.3)

project(alxlib)

include_directories(
	${PROJECT_SOURCE_DIR}/../../src
	${PROJECT_SOURCE_DIR}/../../include/)

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/../../src/*.c)

add_library(
	alxlib STATIC ${SRC}
	${PROJECT_SOURCE_DIR}/../../bin/)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -Wextra -Wshadow -Wmissing-prototypes -Wstrict-prototypes")

set(CMAKE_BUILD_TYPE Debug)