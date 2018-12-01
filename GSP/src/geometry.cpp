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

glm::mat4x4 Geometry::getPerspectiveMatrix(float r, float l, float t, float b, float f, float n) {
	glm::mat4x4 matrix;
	matrix = glm::mat4x4(glm::vec4(2 * n / (r - l), 0, (r + l) / (r - l), 0),
						 glm::vec4(0, 2 * n / (t - b), (t + b) / (t - b), 0),
						 glm::vec4(0, 0, -1 * (f + n) / (f - n), -2 * n * f / (f - n)),
		 				 glm::vec4(0, 0, -1, 0)
						);
	return matrix;
}

glm::mat4x4 Geometry::getCoordinateMatrix(glm::vec3 u, glm::vec3 v, glm::vec3 w, glm::vec3 e) {
	glm::mat4x4 matrix;
	matrix = glm::mat4x4(glm::vec4(u.x, v.x, w.x, e.x),
						 glm::vec4(u.y, v.y, w.y, e.y),
						 glm::vec4(u.z, v.z, w.z, e.z),
						 glm::vec4(0, 0, 0, 1)
	);
	return matrix;
}

glm::mat4x4 Geometry::getViewMatrix(float x, float y) {
	glm::mat4x4 matrix;
	matrix = glm::mat4x4(glm::vec4(x / 2, 0, 0, (x - 1) / 2),
						 glm::vec4(0, y / 2, 0, (y -1) / 2),
						 glm::vec4(0, 0, 1, 0),
						 glm::vec4(0, 0, 0, 1)
	);
	return matrix;
}