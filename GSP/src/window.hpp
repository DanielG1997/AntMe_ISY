#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "SDL.h"
#include "geometry.hpp"
#include <GLEW/glew.h>
#include <Windows.h>

class Window{
 public:
  unsigned int width, height;

  Window(unsigned int width, unsigned int height);

  void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
  void clear();
  void swap();

  //void drawTriangles();
  //void drawTetrahedron(float degrees);

  //GLuint createProgramWithShaders(const char* vertexsource, const char* fragmentsource);
  //void deleteShaderObjects();

 private:
  SDL_Window* window_ = nullptr;

  //GLuint vertexobject;
  //GLuint bufferobject;
  //GLuint vertexshader;
  //GLuint fragmentshader;
  //GLuint shaderprogram;
};

#endif  // WINDOW_HPP_
