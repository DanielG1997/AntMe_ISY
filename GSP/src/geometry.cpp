#include "geometry.hpp"

glm::mat4x4 Geometry::getRotationMatrix(char axis, float angle) {
	glm::mat4x4 matrix;
	if (axis == 'x' || axis == 'X') {
		matrix = glm::mat4x4 (glm::vec4(1, 0, 0, 0),
							  glm::vec4(0, cos(angle * glm::pi<float>() / 180), -1* sin(angle * glm::pi<float>() / 180), 0),
							  glm::vec4(0, sin(angle * glm::pi<float>() / 180), cos(angle * glm::pi<float>() / 180), 0),
							  glm::vec4(0, 0, 0, 1)
							 );
	}
	else if (axis == 'y' || axis == 'Y') {
		matrix = glm::mat4x4(glm::vec4(cos(angle * glm::pi<float>() / 180), 0, sin(angle * glm::pi<float>() / 180), 0),
						     glm::vec4(0, 1, 0, 0),
						 	 glm::vec4(-1 * sin(angle * glm::pi<float>() / 180), 0, cos(angle * glm::pi<float>() / 180), 0),
							 glm::vec4(0, 0, 0, 1)
							);
	}
	else if (axis == 'z' || axis == 'Z') {
		matrix = glm::mat4x4(glm::vec4(cos(angle * glm::pi<float>() / 180), -1 * sin(angle * glm::pi<float>() / 180), 0, 0),
							 glm::vec4(sin(angle * glm::pi<float>() / 180), cos(angle * glm::pi<float>() / 180), 0, 0),
							 glm::vec4(0, 0, 1, 0),
							 glm::vec4(0, 0, 0, 1)
							);
	}
	return matrix;
}

glm::mat4x4 Geometry::getTranslationMatrix(glm::vec3 trans) {
	glm::mat4x4 matrix;
	matrix = glm::mat4x4(glm::vec4(1, 0, 0, trans.x),
						 glm::vec4(0, 1, 0, trans.y),
						 glm::vec4(0, 0, 1, trans.z),
						 glm::vec4(0, 0, 0, 1)
						);
	return matrix;
}

glm::mat4x4 Geometry::getScaleMatrix(glm::vec3 scale) {
	glm::mat4x4 matrix;
	matrix = glm::mat4x4(glm::vec4(scale.x, 0, 0, 0),
						 glm::vec4(0, scale.y, 0, 0),
						 glm::vec4(0, 0, scale.z, 0),
						 glm::vec4(0, 0, 0, 1)
						);
	return matrix;
}

glm::mat4x4 Geometry::getShearMatrix(char axis, glm::vec3 shear) {
	glm::mat4x4 matrix;
	if (axis == 'x' || axis == 'X') {
		matrix = glm::mat4x4(glm::vec4(1, shear.y, shear.z, 0),
							 glm::vec4(0, 1, 0, 0),
							 glm::vec4(0, 0, 1, 0),
							 glm::vec4(0, 0, 0, 1)
							);
	}
	else if (axis == 'y' || axis == 'Y') {
		matrix = glm::mat4x4(glm::vec4(1, 0, 0, 0),
							 glm::vec4(shear.x, 1, shear.z, 0),
							 glm::vec4(0, 0, 1, 0),
							 glm::vec4(0, 0, 0, 1)
							);
	}
	else if (axis == 'z' || axis == 'Z') {
		matrix = glm::mat4x4(glm::vec4(1, 0, 0, 0),
							 glm::vec4(0, 1, 0, 0),
							 glm::vec4(shear.x, shear.y, 1, 0),
							 glm::vec4(0, 0, 0, 1)
		);
	}
	return matrix;
}