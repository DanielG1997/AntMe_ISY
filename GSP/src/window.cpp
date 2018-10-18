#include "window.hpp"
#include <glew.h>

Window::Window(unsigned int width, unsigned int height) {
  SDL_Init(SDL_INIT_VIDEO);

  window_ =
      SDL_CreateWindow("GSP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_OPENGL);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_CreateContext(window_);

  glewExperimental = GL_TRUE;
  glewInit();
}
//
//void Window::swap(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
//	glClearColor(red, green, blue, alpha);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	SDL_GL_SwapWindow(window_);
//}