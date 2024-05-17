#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

int running = 1;

struct Player {
  int x;
  int y;
  int dir;
} typedef Player;

Player player = {10, 10, 0};

#define STOP 0
#define RIGHT 1
#define LEFT -1

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_Q)
    glfwSetWindowShouldClose(window, 1);
  if (key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(window, 1);

  if (key == GLFW_KEY_A)
    player.dir = action == GLFW_RELEASE ? STOP : LEFT;
  if (key == GLFW_KEY_D)
    player.dir = action == GLFW_RELEASE ? STOP : RIGHT;
}

void update() {
  int speed = 10;
  player.x += speed * player.dir;

  // printf("x=%d y=%d dir=%d\n", player.x, player.y, player.dir);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void load_shader(const char *path, char *buf, int buf_size) {
  FILE *f = fopen(path, "r");
  if (!f) {
    puts("failed to load shader");
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);
  if (fsize > buf_size)
    fsize = buf_size;
  fread(buf, buf_size, 1, f);
  buf[fsize] = 0;
  fclose(f);
}

void check_compile_errors(unsigned int shader) {
  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info[512];
    glGetShaderInfoLog(shader, sizeof(info), NULL, info);
    fprintf(stderr, "failed to compile shader: %s\n", info);
    exit(1);
  }
}

int main() {
  puts("hello world");

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(800, 600, "UwU OpenGL", NULL, NULL);
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
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // clang-format off
  float vertices[] = {
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
  };
  // clang-format on

  char aBasicVertex[512];
  load_shader("data/shaders/basic_vertex.glsl", aBasicVertex,
              sizeof(aBasicVertex));
  const char *s = aBasicVertex;

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &s, NULL);
  glCompileShader(vertexShader);
  check_compile_errors(vertexShader);

  char aBasicFragment[512];
  load_shader("data/shaders/basic_fragment.glsl", aBasicFragment,
              sizeof(aBasicFragment));
  const char *sf = aBasicFragment;

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &sf, NULL);
  glCompileShader(fragmentShader);
  check_compile_errors(fragmentShader);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glLinkProgram(shaderProgram);

  int success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    char info[512];
    glGetProgramInfoLog(shaderProgram, sizeof(info), NULL, info);
    fprintf(stderr, "failed to link shader: %s", info);
    return -1;
  }

  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    update();

    if (!running)
      break;
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
}
