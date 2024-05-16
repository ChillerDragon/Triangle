#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

int running = 1;

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    running = 0;
}

int main() {
  puts("hello world");

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    puts("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    printf("Error: %s\n", glewGetErrorString(err));
    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetKeyCallback(window, key_callback);

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();

    if (!running)
      break;
  }
}
