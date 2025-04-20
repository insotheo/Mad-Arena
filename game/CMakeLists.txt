cmake_minimum_required(VERSION 3.10)

project(Game)
set(GAME_NAME "MadArena")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(GAME_LIBS
FLAC
freetype
ogg
sfml-audio
sfml-graphics
sfml-main
sfml-system
sfml-window
vorbis
vorbisenc
vorbisfile
)

file(GLOB GAME_SOURCES
src/main.cpp
)

add_executable(${GAME_NAME} ${GAME_SOURCES})

target_link_libraries(${GAME_NAME} PRIVATE ${GAME_LIBS})