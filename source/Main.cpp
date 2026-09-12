#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <array>

// clang-format off
std::array<GLfloat, 18> vertices {
  -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
   0.0f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
   0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
};
// clang-format on

const char *vertexShaderSource = R"(
#version 460 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;

out vec3 ourColor;

void main() {
  gl_Position = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0f);
  ourColor = vertexColor;
}
)";

const char *fragmentShaderSource = R"(
#version 460 core

out vec4 color;

in vec3 ourColor;

void main() {
  color = vec4(ourColor, 1.0f);
}
)";

void FramebufferSizeCallback(GLFWwindow *window, GLint w, GLint h) {
  glViewport(0, 0, w, h);
}

void HandleInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
  if (!window) {
    std::cout << "Failed to create a window. Terminating..." << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD. Terminating..." << std::endl;
    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, 800, 600);

  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

  GLuint vertexShader = 0;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  GLuint fragmentShader = 0;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  GLuint shaderProgram = 0;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices[0]) * vertices.size()),
      vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(
      0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
      (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    HandleInput(window);

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}
