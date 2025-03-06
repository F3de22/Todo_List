cmake_minimum_required(VERSION 3.25)
project(LabProgrammazione)

set(CMAKE_CXX_STANDARD 17)

add_executable(LabProgrammazione main.cpp Task.h TodoList.h)

add_subdirectory(test)

set(SOURCE_FILES main.cpp Task.h TodoList.h)
add_executable(unit_testing main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(unit_testing core)
