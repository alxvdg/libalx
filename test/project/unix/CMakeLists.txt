cmake_minimum_required(VERSION 3.3)

project(tests)

include_directories(
	${PROJECT_SOURCE_DIR}/../../../code/include/
	${PROJECT_SOURCE_DIR}/../../../code/src/)

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/../../src/main.c ${PROJECT_SOURCE_DIR}/../../src/tests/*.c)

link_directories(${PROJECT_SOURCE_DIR}/../../../code/project/unix/)

add_executable(tests ${SRC})

target_link_libraries(tests PRIVATE alxlib m)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -Wshadow -Wmissing-prototypes -Wstrict-prototypes")

set(CMAKE_BUILD_TYPE Debug)