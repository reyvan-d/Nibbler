cmake_minimum_required(VERSION 3.7)
project (nibbler)

set(
        CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_HOME_DIRECTORY}/libs
)
set(
        CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_HOME_DIRECTORY}
)

include_directories(includes)

#shared libraries
file(GLOB LIBS1 "libs/src/lib1/*.cpp")
file(GLOB LIBS2 "libs/src/lib2/*.cpp")
file(GLOB LIBS3 "libs/src/lib3/*.cpp")
add_library(lib1 SHARED ${LIBS1})
add_library(lib2 SHARED ${LIBS2})
add_library(lib3 SHARED ${LIBS3})

#executable
file(GLOB SOURCES "src/*.cpp")
add_executable(nibbler ${SOURCES})