#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "window.hpp"
#include "mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <stdio.h>

class Scene {
 public:
	 Scene(const std::string path);
	 void render(GLuint shaderprogram);

	 std::vector<Mesh> meshes;
	 std::vector<Texture> textures_loaded;
 private:
	 //const std::string filename = R"(C:\Users\Daniel\Documents\GitHub\AntMe_ISY\GSP\object\Circlemaze\Circlemaze.obj)";
	 std::string directory;

	 void processNode(aiNode* node, const aiScene* scene);
	 Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	 std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	 unsigned int TextureFromFile(const char *filename, const std::string &directory, bool gamma);
};

#endif  // SCENE_HPP_