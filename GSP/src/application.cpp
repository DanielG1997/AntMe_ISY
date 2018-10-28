#include "application.hpp"
#include <iostream>

Application::Application() : window_(900, 600) {}

int Application::Run() {
  SDL_Event event;
  bool runs = true;
  while (runs) {
    while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			runs = false;
			break;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_R:
				window_.swapColor(1, 0, 0, 0);
				break;
			case SDL_SCANCODE_G:
				window_.swapColor(0, 1, 0, 0);
				break;
			case SDL_SCANCODE_B:
				window_.swapColor(0, 0, 1, 0);
				break;
			case SDL_SCANCODE_K:
				window_.swapColor(0, 0, 0, 0);
				break;
			case SDL_SCANCODE_W:
				window_.swapColor(1, 1, 1, 0);
				break;
			//Dreiecke zeichnen
			case SDL_SCANCODE_T:
				window_.createTriangles();
				break;
			}
		}
    }
  }
  return EXIT_SUCCESS;
}