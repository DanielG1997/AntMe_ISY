#include "scene.hpp"

Scene::Scene() {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, 0);

	if (!scene)
	{
		printf("%s\n", importer.GetErrorString());
	}
}