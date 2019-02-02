#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>


class Scene {
 public:
	 Scene();
 private:
	 const std::string filename = R"(C:\Users\Daniel\Documents\GitHub\AntMe_ISY\GSP\object\ufo\ufo.obj)";
};

#endif  // SCENE_HPP_