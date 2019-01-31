#include "scene.hpp"

Scene::Scene() {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, 0);
	//FILE* file = fopen(filename, "r");

	if (!scene)
	{
		printf("%s\n", importer.GetErrorString());
	}
}