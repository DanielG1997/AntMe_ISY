#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "SDL.h"
#include <Windows.h>
#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <math.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>

class Window {
 public:
  Window(unsigned int width, unsigned int height);

  void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
  void swap();
  void drawTriangles();
  void drawTetraeder();

 private:
  SDL_Window* window_ = nullptr;
};

#endif  // WINDOW_HPP_
