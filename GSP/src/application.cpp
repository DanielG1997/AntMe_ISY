#include "application.hpp"
#include <iostream>

Application::Application() : window_(960, 600) {}

int Application::Run() {
  SDL_Event event;
  bool runs = true;
  bool flag = false;
  float degrees = 0.0;
  while (runs) {
    while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			runs = false;
			break;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_R:
				flag = false;
				window_.setColor(1, 0, 0, 0);
				window_.clear();
				break;
			case SDL_SCANCODE_G:
				flag = false;
				window_.setColor(0, 1, 0, 0);
				window_.clear();
				break;
			case SDL_SCANCODE_B:
				flag = false;
				window_.setColor(0, 0, 1, 0);
				window_.clear();
				break;
			case SDL_SCANCODE_K:
				flag = false;
				window_.setColor(0, 0, 0, 0);
				window_.clear();
				break;
			case SDL_SCANCODE_W:
				flag = false;
				window_.setColor(1, 1, 1, 0);
				window_.clear();
				break;
			//Dreiecke zeichnen
			case SDL_SCANCODE_D:
				flag = false;
				window_.setColor(1, 1, 1, 1);
				window_.clear();
				window_.drawTriangles();
				break;
			//Tetraeder zeichnen
			case SDL_SCANCODE_T:
				flag = true;
				break;
			}
		}
		if (!flag) {
			window_.swap();
		}
		Sleep(100);
    }
	if (flag) {
		//window_.setColor(1, 1, 1, 1);
		window_.clear();
		window_.drawTetrahedron(degrees);
		degrees = (degrees + 1);
		if (degrees == 360)
			degrees = 0;
		window_.swap();
	}
  }
  return EXIT_SUCCESS;
}