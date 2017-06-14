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
set(CMAKE_PREFIX_PATH "~/")
set(CMAKE_CXX_FLAGS "-std=c++14")
set(SDL2_INCLUDE_DIR "/nfs/zfs-student-6/users/reyvan-d/.brew/include/SDL2")
set(SDL2_LIBRARY "/nfs/zfs-student-6/users/reyvan-d/.brew/lib/libSDL2.dylib")

include_directories(includes ${SDL2_INCLUDE_DIR})

#shared libraries
file(GLOB LIBS1 "libs/src/lib1/*.cpp")
file(GLOB LIBS2 "libs/src/lib2/*.cpp")
file(GLOB LIBS3 "libs/src/lib3/*.cpp")
add_library(lib1 SHARED ${LIBS1} libs/src/lib1/render.cpp libs/src/lib1/lib1.h)
add_library(lib2 SHARED ${LIBS2} libs/src/lib2/lib2.h)
add_library(lib3 SHARED ${LIBS3} libs/src/lib3/lib3.h)

set(LINK_LIB1 lib1)
set(LINK_LIB2 lib2)
set(LINK_LIB3 lib3)

#executable
file(GLOB SOURCES "src/*.cpp")
add_executable(nibbler ${SOURCES})
target_link_libraries(nibbler dl)
target_link_libraries(${LINK_LIB1} ${SDL2_LIBRARY})
target_link_libraries(nibbler ${SDL2_LIBRARY})
target_link_libraries(nibbler ${LINK_LIB1})
target_link_libraries(nibbler ${LINK_LIB2})
target_link_libraries(nibbler ${LINK_LIB3})