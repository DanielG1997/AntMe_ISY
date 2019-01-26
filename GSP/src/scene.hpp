#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Scene {
 public:
	 Scene();
 private:
	 const std::string filename = "ufo.obj";
	 const aiScene* scene;
};

#endif  // SCENE_HPP_