#include "application.hpp"
#include <iostream>

Application::Application() : window_(1280, 800) {}

int Application::Run() {
  SDL_Event event;
  while (true) {
    while (SDL_PollEvent(&event)) {
		/*if (SDL_SCANCODE_R)
			glClearColor(1, 0, 0, 0);
		else if (SDL_SCANCODE_G)
			glClearColor(0, 1, 0, 0);
		else if (SDL_SCANCODE_B)
			glClearColor(0, 0, 1, 0);
		break;*/
    }
  }
  return EXIT_SUCCESS;
}
