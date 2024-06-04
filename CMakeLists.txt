cmake_minimum_required(VERSION 3.24)
project(sopki VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include_directories(src)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES}) 

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})