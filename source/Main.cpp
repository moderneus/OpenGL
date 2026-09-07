#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <array>

// clang-format off
std::array<GLfloat, 9> firstTriangle{
  -1.0f, -0.5f, 0.0f,
  -0.5f,  0.5f, 0.0f,
   0.0f, -0.5f, 0.0f,

};
std::array<GLfloat, 9> secondTriangle{
   0.0f, -0.5f, 0.0f,
   0.5f,  0.5f, 0.0f,
   1.0f, -0.5f, 0.0f,
};
// clang-format on

const char *vertexShaderSource = R"(
#version 460 core

layout (location = 0) in vec3 vertex;

void main() {
  gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.0f);
}
)";

const char *firstFragmentShaderSource = R"(
#version 460 core

out vec4 color;

void main() {
  color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
)";

const char *secondFragmentShaderSource = R"(
#version 460 core

out vec4 color;

void main() {
  color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
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

  // vertex shader for both the triangles
  GLuint vertexShader = 0;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  // fragment shader for the first triangle
  GLuint firstFragmentShader = 0;
  firstFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(firstFragmentShader, 1, &firstFragmentShaderSource, nullptr);
  glCompileShader(firstFragmentShader);

  // shader program for the first triangle
  GLuint firstShaderProgram = 0;
  firstShaderProgram = glCreateProgram();

  glAttachShader(firstShaderProgram, vertexShader);
  glAttachShader(firstShaderProgram, firstFragmentShader);
  glLinkProgram(firstShaderProgram);

  glDeleteShader(firstFragmentShader);

  // fragment shader for the second triangle
  GLuint secondFragmentShader = 0;
  secondFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(secondFragmentShader, 1, &secondFragmentShaderSource, nullptr);
  glCompileShader(secondFragmentShader);

  // shader program for the second triangle
  GLuint secondShaderProgram = 0;
  secondShaderProgram = glCreateProgram();

  glAttachShader(secondShaderProgram, vertexShader);
  glAttachShader(secondShaderProgram, secondFragmentShader);
  glLinkProgram(secondShaderProgram);

  // delete the shaders
  glDeleteShader(vertexShader);
  glDeleteShader(secondFragmentShader);

  // first triangle
  GLuint firstTriangleVAO = 0;
  glGenVertexArrays(1, &firstTriangleVAO);
  glBindVertexArray(firstTriangleVAO);

  GLuint firstTriangleVBO = 0;
  glGenBuffers(1, &firstTriangleVBO);
  glBindBuffer(GL_ARRAY_BUFFER, firstTriangleVBO);
  glBufferData(GL_ARRAY_BUFFER,
      (sizeof(firstTriangle[0]) * firstTriangle.size()), firstTriangle.data(),
      GL_STATIC_DRAW);

  glVertexAttribPointer(
      0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  // second triangle
  GLuint secondTriangleVAO = 0;
  glGenVertexArrays(1, &secondTriangleVAO);
  glBindVertexArray(secondTriangleVAO);

  GLuint secondTriangleVBO = 0;
  glGenBuffers(1, &secondTriangleVBO);
  glBindBuffer(GL_ARRAY_BUFFER, secondTriangleVBO);
  glBufferData(GL_ARRAY_BUFFER,
      (sizeof(secondTriangle[0]) * secondTriangle.size()),
      secondTriangle.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(
      0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    HandleInput(window);

    glClear(GL_COLOR_BUFFER_BIT);

    // first triangle
    glUseProgram(firstShaderProgram);
    glBindVertexArray(firstTriangleVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // second triangle
    glUseProgram(secondShaderProgram);
    glBindVertexArray(secondTriangleVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}
