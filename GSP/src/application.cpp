#include "application.hpp"
#include <iostream>

Application::Application() : window_(800, 500) {}

int Application::Run() {
  SDL_Event event;
  bool runs = true;
  while (runs) {
    while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			runs = false;
			return EXIT_SUCCESS;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_R:
				window_.swap(1, 0, 0, 0);
				break;
			case SDL_SCANCODE_G:
				window_.swap(0, 1, 0, 0);
				break;
			case SDL_SCANCODE_B:
				window_.swap(0, 0, 1, 0);
				break;
			case SDL_SCANCODE_K:
				window_.swap(0, 0, 0, 0);
				break;
			case SDL_SCANCODE_W:
				window_.swap(1, 1, 1, 0);
				break;
			}
		}
    }
  }
  return EXIT_SUCCESS;
}
