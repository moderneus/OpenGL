cmake_minimum_required(VERSION 3.28)

project(OpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(libs/glfw)

add_library(glad STATIC libs/glad/src/gl.c)
target_include_directories(glad PUBLIC libs/glad/include)

file(GLOB SOURCE "source/*.cpp")

add_executable(OpenGL ${SOURCE})

target_compile_options(OpenGL PRIVATE -g -Wall -O0)
target_link_libraries(OpenGL PRIVATE glfw glad)
target_include_directories(OpenGL PRIVATE include libs/glfw/include libs/glad/include)

if(WIN32)
  file(GLOB_RECURSE SHARED_LIBS ${CMAKE_BINARY_DIR}/libs/*.dll)
elseif(LINUX)
  file(GLOB_RECURSE SHARED_LIBS ${CMAKE_BINARY_DIR}/libs/*.so)
endif()

foreach(LIB_PATH ${SHARED_LIBS})
    add_custom_command(
        TARGET OpenGL 
        POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LIB_PATH}" "$<TARGET_FILE_DIR:OpenGL>"
    )
endforeach()
