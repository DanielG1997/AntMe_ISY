#include "application.hpp"
#include <iostream>

Application::Application() : window_(960, 600) {}

int Application::Run() {
  SDL_Event event;
  bool runs = true;
  bool flag = false;
  int count = 0;
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
				/*window_.setColor(1, 1, 1, 1);
				window_.clear();
				window_.drawTetrahedron(count);
				count = (count + 10) % 360;*/
				flag = true;
				break;
			}
		}
		if (flag) {
			window_.setColor(1, 1, 1, 1);
			window_.clear();
			window_.drawTetrahedron(count);
			count = (count + 5) % 360;
		}
		Sleep(50);
		window_.swap();
    }
  }
  return EXIT_SUCCESS;
}