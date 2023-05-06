cmake_minimum_required(VERSION 3.12)
project(main)

set(CMAKE_C_STANDARD 11)

LINK_LIBRARIES(m pthread)

file(REMOVE_RECURSE "cmake-build-debug")
file(GLOB_RECURSE SRC src/*.c)

add_executable(main ${SRC})
