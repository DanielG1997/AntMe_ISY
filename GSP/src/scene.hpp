#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "window.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <stdio.h>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
};

struct Texture {
	unsigned int id;
	std::string type;
};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures) { this->vertices = vertices; this->textures = textures; };
};

class Scene {
 public:
	 Scene();
 private:
	 const std::string filename = R"(C:\Users\Daniel\Documents\GitHub\AntMe_ISY\GSP\object\ufo\ufo.obj)";

	 std::vector<Mesh> meshes;
	 std::string directory;

	 void processNode(aiNode* node, const aiScene* scene);
	 Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif  // SCENE_HPP_