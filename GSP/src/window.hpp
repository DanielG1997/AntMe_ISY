#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "SDL.h"
#include "geometry.hpp"
#include <GLEW/glew.h>
#include <Windows.h>

class Window : public Geometry{
 public:
  Window(unsigned int width, unsigned int height);

  void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
  void clear();
  void swap();

  void drawTriangles();
  void drawTetrahedron(int count);

  GLuint createProgramWithShaders(const char* vertexsource, const char* fragmentsource);
  void createVertexAndBufferObjects();

 private:
  SDL_Window* window_ = nullptr;
};

#endif  // WINDOW_HPP_
