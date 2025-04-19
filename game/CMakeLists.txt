cmake_minimum_required(VERSION 3.10)

project(Game)
set(GAME_NAME "MadArena")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

file(GLOB GAME_SOURCES
src/main.cpp
)

add_executable(${GAME_NAME} ${GAME_SOURCES})