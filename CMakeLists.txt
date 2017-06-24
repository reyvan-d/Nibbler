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
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(CMAKE_PREFIX_PATH "~/")
set(CMAKE_CXX_STANDARD 11)

#Windows
set(SDL2_INCLUDE_DIR "C:/SDL/i686-w64-mingw32/include/SDL2")
set(SDL2_LIBRARY "C:/SDL/i686-w64-mingw32/lib/libSDL2.a")

set(SFML_INCLUDE_DIR "C:/SFML/include")
find_package(SFML 2 REQUIRED network audio graphics window system)

set(GLEW_INCLUDE_DIR "C:/GLEW/include")
set(GLEW_STATIC_LIBRARY "C:/GLEW/lib/Win32/glew32.lib")
set(FREEGLUT_INCLUDE_DIR "C:/FreeGlut/include")
set(GLEW_LIBRARY "C:/GLEW/bin/Release/Win32/glew32.dll")
set(FREEGLUT_LIBRARY "C:/FreeGlut/lib/libfreeglut.a")


#OSX
#set(SDL2_INCLUDE_DIR "/nfs/zfs-student-6/users/reyvan-d/.brew/include/SDL2")
#set(SDL2_LIBRARY "/nfs/zfs-student-6/users/reyvan-d/.brew/lib/libSDL2.dylib")

#set(SFML_INCLUDE_DIR "/nfs/zfs-student-6/users/reyvan-d/.brew/include")
#find_package(SFML REQUIRED graphics window system)

#set(GLEW_INCLUDE_DIR "/nfs/zfs-student-6/users/reyvan-d/.brew/include/GL")
#set(FREEGLUT_LIBRARY "/nfs/zfs-student-6/users/reyvan-d/.brew/lib/libglut.dylib")
#set(GLEW_LIBRARY "/nfs/zfs-student-6/users/reyvan-d/.brew/lib/libGLEW.dylib")

#Linux
# set(SDL2_INCLUDE_DIR "/usr/include/SDL2")


include_directories(includes ${SDL2_INCLUDE_DIR} ${SFML_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${FREEGLUT_INCLUDE_DIR})

#shared libraries
file(GLOB LIBS1 "libs/src/lib1/*.cpp")
file(GLOB LIBS2 "libs/src/lib2/*.cpp")
file(GLOB LIBS3 "libs/src/lib3/*.cpp")
add_library(lib1 SHARED ${LIBS1} libs/src/lib1/render.cpp libs/src/lib1/lib1.h libs/src/lib1/cleanup.h)
add_library(lib2 SHARED ${LIBS2} libs/src/lib2/lib2.h libs/src/lib2/featured_renderer.h)
add_library(lib3 SHARED ${LIBS3} libs/src/lib3/lib3.h)

set(LINK_LIB1 lib1)
set(LINK_LIB2 lib2)
set(LINK_LIB3 lib3)

#executable
file(GLOB SOURCES "src/*.cpp")
add_executable(nibbler ${SOURCES})

#Windows
target_link_libraries(${LINK_LIB1} ${SDL2_LIBRARY} mingw32 m dinput8 dxguid dxerr8 user32 winmm imm32 ole32 oleaut32 shell32 version uuid)
target_link_libraries(${LINK_LIB2} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(${LINK_LIB3} ${FREEGLUT_LIBRARY} ${GLEW_LIBRARY} ${GLEW_STATIC_LIBRARY} "-lopengl32 -lglu32 -lWs2_32 -lole32 -lcomctl32 -lgdi32 -lcomdlg32 -luuid")

#OSX
#target_link_libraries(${LINK_LIB1} ${SDL2_LIBRARY})
#target_link_libraries(${LINK_LIB1} ${SDL2_GFX_LIBRARY})
#target_link_libraries(${LINK_LIB2} /nfs/zfs-student-6/users/reyvan-d/.brew/Cellar/sfml/2.4.2/lib/libsfml-graphics.2.4.2.dylib)
#target_link_libraries(${LINK_LIB2} /nfs/zfs-student-6/users/reyvan-d/.brew/Cellar/sfml/2.4.2/lib/libsfml-window.2.4.2.dylib)
#target_link_libraries(${LINK_LIB2} /nfs/zfs-student-6/users/reyvan-d/.brew/Cellar/sfml/2.4.2/lib/libsfml-system.2.4.2.dylib)
#target_link_libraries(${LINK_LIB3} ${GLEW_LIBRARY} ${FREEGLUT_LIBRARY} "-framework OpenGL")

#if (SFML_FOUND)
#target_link_libraries(${LINK_LIB2} ${SFML_LIBRARIES})
#endif()
#Linux
#target_link_libraries(nibbler dl)
#target_link_libraries(${LINK_LIB1} SDL2)
#target_link_libraries(${LINK_LIB2} sfml-graphics sfml-window sfml-system)
#target_link_libraries(${LINK_LIB2} lGLEW )


#Generic
#target_link_libraries(nibbler ${SDL2_LIBRARY})
target_link_libraries(nibbler ${LINK_LIB1})
target_link_libraries(nibbler ${LINK_LIB2})
target_link_libraries(nibbler ${LINK_LIB3})