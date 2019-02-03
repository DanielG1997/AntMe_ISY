#include "scene.hpp"

Scene::Scene() {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("%s\n", importer.GetErrorString());
		return;
	}
	directory = filename.substr(0, filename.find_last_of('\\' + 1));

	processNode(scene->mRootNode, scene);
}

void Scene::processNode(aiNode* node, const aiScene* scene)
{
	if (node == nullptr)
	{
		return;
	}

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Scene::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Vertex vertex;
			glm::vec3 vector;

			vector.x = mesh->mVertices[mesh->mFaces[i].mIndices[j]].x;
			vector.y = mesh->mVertices[mesh->mFaces[i].mIndices[j]].y;
			vector.z = mesh->mVertices[mesh->mFaces[i].mIndices[j]].z;
			vertex.position = vector;

			vector.x = mesh->mNormals[mesh->mFaces[i].mIndices[j]].x;
			vector.y = mesh->mNormals[mesh->mFaces[i].mIndices[j]].y;
			vector.z = mesh->mNormals[mesh->mFaces[i].mIndices[j]].z;
			vertex.normal = vector;

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x;
				vec.y = mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y;
				vertex.texture = vec;
			}
			else
			{
				vertex.texture = glm::vec2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	return Mesh(vertices, textures);
}