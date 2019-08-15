#ifndef MESH_HPP_
#define MESH_HPP_

#include "window.hpp"
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures) { this->vertices = vertices; this->textures = textures; };
	void render(GLuint shaderprogram);
};

#endif  // MESH_HPP_