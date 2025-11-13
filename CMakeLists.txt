cmake_minimum_required(VERSION 4.1.2)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(PROJECT_NAME "OpenGL")

project(${PROJECT_NAME} LANGUAGES C CXX)

find_package(fmt REQUIRED)
find_package(SDL3 REQUIRED)

set(GLAD libs/src/glad)

add_executable(${PROJECT_NAME}

    #--LIBS--#
    ${GLAD}/glad.c

    #--SRC--#
    src/Main.cpp

    src/Renderer/Window.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/VAO.cpp
    src/Renderer/VBO.cpp
    
    src/Shaders/Shader.cpp
    
    src/Utils/Logger.cpp

)

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE headers libs/headers)
target_link_libraries(${PROJECT_NAME} fmt::fmt SDL3::SDL3)
