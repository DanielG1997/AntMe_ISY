#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <glm/glm.hpp>
#include <iostream>
#include <stdlib.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class Geometry{
 public:
	 glm::mat4x4 getRotationMatrix(char axis, float angle = 30.0f);
	 glm::mat4x4 getTranslationMatrix(glm::vec3 trans);
	 glm::mat4x4 getScaleMatrix(glm::vec3 scale);
	 glm::mat4x4 getShearMatrix(char axis, glm::vec3 shear);
	 glm::mat4x4 getPerspectiveMatrix(float r, float l, float t, float b, float f, float n);
	 glm::mat4x4 getCameraMatrix(glm::vec3 u, glm::vec3 v, glm::vec3 w, glm::vec3 e, char type);
	 //glm::mat4x4 getViewMatrix(float x, float y);
};

#endif  // GEOMETRY_HPP_