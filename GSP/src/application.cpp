#include "application.hpp"
#include <iostream>

Application::Application() : window_(960, 600) {}

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
				window_.setColor(1, 0, 0, 0);
				window_.clear();
				window_.swap();
				break;
			case SDL_SCANCODE_G:
				window_.setColor(0, 1, 0, 0);
				window_.clear();
				window_.swap();
				break;
			case SDL_SCANCODE_B:
				window_.setColor(0, 0, 1, 0);
				window_.clear();
				window_.swap();
				break;
			case SDL_SCANCODE_K:
				window_.setColor(0, 0, 0, 0);
				window_.clear();
				window_.swap();
				break;
			case SDL_SCANCODE_W:
				window_.setColor(1, 1, 1, 0);
				window_.clear();
				window_.swap();
				break;
			//Dreiecke zeichnen
			case SDL_SCANCODE_D:
				window_.setColor(1, 1, 1, 1);
				window_.clear();
				window_.drawTriangles();
				window_.swap();
				break;
			//Tetraeder zeichnen
			case SDL_SCANCODE_T:
				window_.setColor(1, 1, 1, 1);
				window_.clear();
				window_.drawTetrahedron();
				window_.swap();
				break;
			}
		}
    }
  }
  return EXIT_SUCCESS;
}