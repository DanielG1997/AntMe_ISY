#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "SDL.h"
#include <glew.h>
#include <Windows.h>
#include <GL/GL.h>

class Window {
 public:
  Window(unsigned int width, unsigned int height);
  void swap(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

 private:
  SDL_Window* window_ = nullptr;
};

#endif  // WINDOW_HPP_
