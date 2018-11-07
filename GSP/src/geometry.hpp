#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_
#define _USE_MATH_DEFINES

#include <glm/glm.hpp>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class Geometry{
 public:
	 Geometry() {};

	 glm::mat4x4 getRotationMatrix(char axis, float angle = 30.0f);
	 glm::mat4x4 getTranslationMatrix(glm::vec3 trans);
	 glm::mat4x4 getScaleMatrix(glm::vec3 scale);
	 glm::mat4x4 getShearMatrix(char axis, glm::vec3 shear);

	 void createShaders(const char &vertexsource, const char &fragmentsource);
};

#endif  // GEOMETRY_HPP_