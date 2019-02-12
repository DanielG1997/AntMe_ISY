#include "renderer.hpp"

Renderer::Renderer(Window* window) {
	this->window = window;

	//create VBO and VAO
	glGenVertexArrays(1, &vertexobject);
	glGenBuffers(1, &bufferobject);

	glBindVertexArray(vertexobject);
	glBindBuffer(GL_ARRAY_BUFFER, bufferobject);
}

GLuint Renderer::createShaderProgram() {
	vertexsource =  "#version 330 core\n"
					"uniform mat4 model_to_world_matrix;\n"
					"uniform vec3 lightposition;\n"
					"uniform vec3 cameraposition;\n"
					"layout(location = 0) in vec3 vertex_position;\n"
					"layout(location = 1) in vec3 normal_position;\n"
					"out vec3 vertex_normal_worldspace;\n"
					"out vec3 h;\n"
					"out vec3 l;\n"
					"void main() {\n"
					"vec4 position = model_to_world_matrix * vec4((vertex_position), 1.0f);\n"
					"vertex_normal_worldspace = (transpose(inverse(model_to_world_matrix)) * vec4((normal_position), 0.0)).xyz;\n"
					"vec3 v = normalize(cameraposition - position.xyz);\n"
					"l = normalize(lightposition - position.xyz);\n"
					"h = normalize(v + l);\n"
					"gl_Position = position;\n"
					"}";

	fragmentsource = "#version 330 core\n"
					 "in vec3 vertex_normal_worldspace;\n"
					 "in vec3 h;\n"
					 "in vec3 l;\n"
					 "uniform vec3 ka, kd, ks, ca, ci;\n"
					 "uniform float phong;\n"
					 "uniform vec3 user_color;\n"
					 "layout(location = 0) out vec3 color;\n"
					 "void main() {\n"
					 "vec3 intensity = ka * ca + kd * ci * max(0.0f, dot(vertex_normal_worldspace, l)) + ks * ci * pow(max(0.0f, dot(vertex_normal_worldspace, h)), phong);\n"
					 "color = intensity * user_color;\n"
					 //"color = intensity;\n"
					 "}";
	
	int success;
	char infoLog[512];

	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexsource, nullptr);
	glCompileShader(vertexshader);

	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentsource, nullptr);
	glCompileShader(fragmentshader);

	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexshader);
	glAttachShader(shaderprogram, fragmentshader);
	glLinkProgram(shaderprogram);

	glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderprogram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(shaderprogram);

	return shaderprogram;
}

void Renderer::deleteShaderProgram() {
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	glDeleteProgram(shaderprogram);
}

void Renderer::draw(glm::mat4x4 camT, glm::mat4x4 camR) {
	//glm::vec3 v0 = glm::vec3(-0.6, -0.6, 0.39);
	//glm::vec3 v1 = glm::vec3(0.6, -0.6, 0.39);
	//glm::vec3 v2 = glm::vec3(0.0, -0.6, -0.78);
	//glm::vec3 v3 = glm::vec3(0.0, 0.6, 0.0);
	////normal vertices should be normalized and are pointing away from the triangleside
	//glm::vec3 n0 = glm::cross((v2 - v0), (v1 - v0));
	//n0 = n0 / glm::length(n0);
	//glm::vec3 n1 = glm::cross((v2 - v1), (v3 - v1));
	//n1 = n1 / glm::length(n1);
	//glm::vec3 n2 = glm::cross((v0 - v2), (v3 - v2));
	//n2 = n2 / glm::length(n2);
	//glm::vec3 n3 = glm::cross((v0 - v3), (v1 - v3));
	//n3 = n3 / glm::length(n3);
	////ground(n0), right(n1), left(n2), back(n3)
	//glm::vec3 data[] = { v0,n0,v1,n0,v2,n0,
	//					 v1,n1,v2,n1,v3,n1,
	//					 v0,n2,v2,n2,v3,n2,
	//					 v0,n3,v1,n3,v3,n3
	//};
	/**********************************************************************************************************************/
	glm::mat4x4 perspective = this->getPerspectiveMatrix(4, -4, 2, -2, 2, 1);
	glm::mat4x4 camera = glm::inverse(camT * camR);

	glm::mat4x4 projection = perspective * camera;

	GLuint shaderprogram = this->createShaderProgram();

	glEnable(GL_DEPTH_TEST);

	//lightinformation using only one lightsource
	//cameraposition
	glm::vec3 campos = glm::vec3(camT[3]);
	GLint cameralocation = glGetUniformLocation(shaderprogram, "cameraposition");
	glUniform3f(cameralocation, campos.x, campos.y, campos.z);
	//lightposition
	GLint lightlocation = glGetUniformLocation(shaderprogram, "lightposition");
	glUniform3f(lightlocation, 0.0f, 10.0f, 0.0f);
	//ambient coefficient
	GLint kalocation = glGetUniformLocation(shaderprogram, "ka");
	glUniform3f(kalocation, 0.5f, 0.5f, 0.5f);
	//diffuse coefficient
	GLint kdlocation = glGetUniformLocation(shaderprogram, "kd");
	glUniform3f(kdlocation, 0.5f, 0.5f, 0.5f);
	//specular coefficient
	GLint kslocation = glGetUniformLocation(shaderprogram, "ks");
	glUniform3f(kslocation, 0.5f, 0.5f, 0.5f);
	//amibient light
	GLint calocation = glGetUniformLocation(shaderprogram, "ca");
	glUniform3f(calocation, 1.0f, 1.0f, 1.0f);
	//lightsourcecolor
	GLint cilocation = glGetUniformLocation(shaderprogram, "ci");
	glUniform3f(cilocation, 1.0f, 1.0f, 0.0f);
	//phong value
	GLint phonglocation = glGetUniformLocation(shaderprogram, "phong");
	glUniform1f(phonglocation, 5.0f);

	//triangleinformation
	GLint matrixlocation = glGetUniformLocation(shaderprogram, "model_to_world_matrix");
	glUniformMatrix4fv(matrixlocation, 1, GL_FALSE, glm::value_ptr(projection));
	//colors
	GLint colorlocation = glGetUniformLocation(shaderprogram, "user_color");
	glUniform3f(colorlocation, 0.7f, 0.7f, 0.7f);

	//Scene scene_(R"(C:\Users\Daniel\Documents\GitHub\AntMe_ISY\GSP\object\ufo\ufo.obj)");
	//scene_.render(shaderprogram);
	Scene scene_1(R"(C:\Users\Daniel\Documents\GitHub\AntMe_ISY\GSP\object\blocks\b01.obj)");
	scene_1.render(shaderprogram);
	//Scene scene_2(R"(C:\Users\Daniel\Documents\GitHub\AntMe_ISY\GSP\object\blocks\b02.obj)");
	//scene_2.render(shaderprogram);
	//Scene scene_3(R"(C:\Users\Daniel\Documents\GitHub\AntMe_ISY\GSP\object\blocks\b03.obj)");
	//scene_3.render(shaderprogram);
	//Scene scene_4(R"(C:\Users\Daniel\Documents\GitHub\AntMe_ISY\GSP\object\blocks\b04.obj)");
	//scene_4.render(shaderprogram);

	//GLint size = sizeof(glm::vec3);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * size, nullptr);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * size, (void*)size);

	//glDrawArrays(GL_TRIANGLES, 0, 12);
	//glUniform3f(colorlocation, 0.0f, 1.0f, 0.0f);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glUniform3f(colorlocation, 1.0f, 0.0f, 0.0f);
	//glDrawArrays(GL_TRIANGLES, 3, 3);
	//glUniform3f(colorlocation, 1.0f, 1.0f, 0.0f);
	//glDrawArrays(GL_TRIANGLES, 6, 3);
	//glUniform3f(colorlocation, 0.0f, 0.0f, 1.0f);
	//glDrawArrays(GL_TRIANGLES, 9, 3);
	this->deleteShaderProgram();
}

glm::mat4x4 Renderer::move(float dist, glm::mat4x4 trans, glm::mat4x4 rot) {
	return glm::translate(trans, dist * glm::vec3(rot[2]));
}

glm::mat4x4 Renderer::turn(float angle, glm::mat4x4 rot) {
	return glm::rotate(rot, angle, glm::vec3(0, 1, 0));
}