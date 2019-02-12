#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "scene.hpp"

class Renderer : public Geometry {
public:
	Renderer(Window* window);

	GLuint createShaderProgram();
	void deleteShaderProgram();

	void draw(glm::mat4x4 camT, glm::mat4x4 camR);
	glm::mat4x4 move(float dist, glm::mat4x4 trans, glm::mat4x4 rot);
	glm::mat4x4 turn(float angle, glm::mat4x4 rot);

private:
	Window* window;

	GLuint vertexobject;
	GLuint bufferobject;
	GLuint vertexshader;
	GLuint fragmentshader;
	GLuint shaderprogram;

	const char* vertexsource;
	const char* fragmentsource;
};
#endif  // RENDERER_HPP_