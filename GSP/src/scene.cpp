#include "scene.hpp"

Scene::Scene() {
	Assimp::Importer importer;

	scene = importer.ReadFile(filename,
		aiProcess_CalcTangentSpace |
		aiProcess_SortByPType);

	if (!scene)
	{
		printf("%s\n", importer.GetErrorString());
	}
}