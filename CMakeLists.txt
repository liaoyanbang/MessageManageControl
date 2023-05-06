cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_C_STANDARD 11)

LINK_LIBRARIES(m pthread)

file(GLOB_RECURSE SRC src/*.c)

add_executable(main ${SRC})
