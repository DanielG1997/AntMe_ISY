#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

class Scene {
 public:
	 Scene();
 private:
	 char* filename = "maze.obj";
	 const aiScene* scene;
};

#endif  // SCENE_HPP_