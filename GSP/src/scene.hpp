#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
};

struct Mesh {
	std::vector<Vertex>* vertices;
	std::vector<Texture>* textures;
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
	 std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif  // SCENE_HPP_