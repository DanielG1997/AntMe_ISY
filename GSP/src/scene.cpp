#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "scene.hpp"

Scene::Scene(const std::string path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("%s\n", importer.GetErrorString());
		return;
	}
	directory = path.substr(0, path.find_last_of('\\' + 1));

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
				vertex.texcoords = vec;
			}
			else
			{
				vertex.texcoords = glm::vec2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, textures);
}

std::vector<Texture> Scene::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{   
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	return textures;
}

unsigned int Scene::TextureFromFile(const char *filename, const std::string &directory)
{
	std::string path = directory + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 2)
			format = GL_RG;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at filename: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void Scene::render(GLuint shaderprogram) {
	for (Mesh mesh : this->meshes) {
		mesh.render(shaderprogram);
	}
}