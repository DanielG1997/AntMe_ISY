#include "application.hpp"
#include <iostream>

Application::Application() : window_(960, 600) {}

int Application::Run() {

  Renderer renderer(&this->window_);

  glm::vec3 e = glm::vec3(0, 2, 2);
  glm::vec3 c = glm::vec3(0, 0, 0);
  glm::vec3 b = -glm::normalize(c - e);
  glm::vec3 s = glm::normalize(glm::cross(glm::vec3(0, 1, 0), b));
  glm::vec3 u = glm::cross(b, s);

  glm::mat4x4 cameratranslation = renderer.getCameraMatrix(s, u, b, e, 'T');
  glm::mat4x4 camerarotation = renderer.getCameraMatrix(s, u, b, e, 'R');

  SDL_Event event;
  bool runs = true;
  //bool flag = false;
  //float degrees = 0.0;
  while (runs) {
	//window_.setColor(0.0, 0.5, 1.0, 1.0);
    while (SDL_PollEvent(&event)) {
		window_.clear();
		if (event.type == SDL_QUIT) {
			runs = false;
			break;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_W :
					cameratranslation = renderer.move(-1.0f, cameratranslation, camerarotation);
					break;

				case SDL_SCANCODE_S:
					cameratranslation = renderer.move(1.0f, cameratranslation, camerarotation);
					break;

				case SDL_SCANCODE_A:
					camerarotation = renderer.turn(-45 * glm::pi<float>() / 180, camerarotation);
					break;

				case SDL_SCANCODE_D:
					camerarotation = renderer.turn(45 * glm::pi<float>() / 180, camerarotation);
					break;

				default:
					break;

			//case SDL_SCANCODE_R:
			//	flag = false;
			//	window_.setColor(1, 0, 0, 0);
			//	window_.clear();
			//	break;
			//case SDL_SCANCODE_G:
			//	flag = false;
			//	window_.setColor(0, 1, 0, 0);
			//	window_.clear();
			//	break;
			//case SDL_SCANCODE_B:
			//	flag = false;
			//	window_.setColor(0, 0, 1, 0);
			//	window_.clear();
			//	break;
			//case SDL_SCANCODE_K:
			//	flag = false;
			//	window_.setColor(0, 0, 0, 0);
			//	window_.clear();
			//	break;
			//case SDL_SCANCODE_W:
			//	flag = false;
			//	window_.setColor(1, 1, 1, 0);
			//	window_.clear();
			//	break;
			////Dreiecke zeichnen
			//case SDL_SCANCODE_D:
			//	flag = false;
			//	window_.setColor(1, 1, 1, 1);
			//	window_.clear();
			//	window_.drawTriangles();
			//	break;
			////Tetraeder zeichnen
			//case SDL_SCANCODE_T:
			//	flag = true;
			//	break;
			}
		}
		renderer.draw(cameratranslation, camerarotation);
		window_.swap();
		//if (!flag) {
		//	window_.swap();
		//}
		//Sleep(100);
    }
	//if (flag) {
	//	//window_.setColor(1, 1, 1, 1);
	//	window_.clear();
	//	window_.drawTetrahedron(degrees);
	//	degrees = (degrees + 1);
	//	if (degrees == 360)
	//		degrees = 0;
	//	window_.swap();
	//}
  }
  return EXIT_SUCCESS;
}