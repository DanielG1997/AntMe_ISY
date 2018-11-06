#include "window.hpp"
#include <iostream>

Window::Window(unsigned int width, unsigned int height) {
  SDL_Init(SDL_INIT_VIDEO);

  window_ =
      SDL_CreateWindow("GSP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_OPENGL);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_CreateContext(window_);

  glewExperimental = GL_TRUE;
  glewInit();
}

void Window::setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap() {
	SDL_GL_SwapWindow(window_);
}

void Window::drawTriangles() {
	//some examples of vec3 data
	glm::vec3 v1 = glm::vec3(1.0, 0.0, 0.0);
	glm::vec3 v2 = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 v3 = glm::vec3(0.0, 0.0, 1.0);
	glm::vec3 v4 = glm::vec3(-1.0, 0.0, 0.0);
	glm::vec3 v5 = glm::vec3(0.0, -1.0, 0.0);
	glm::vec3 v6 = glm::vec3(0.0, 0.0, -1.0);
	glm::vec3 data[] = { v1,v2,v3,v4,v5,v6 };
	

	//source for both shaders
	const char* vertexsource = "#version 330 core\n"
							   "layout(location = 0) in vec3 vertex_position;\n"
						       "void main() {\n"
						       "gl_Position.xyz = vertex_position;\n"
						       "gl_Position.w = 1.0;\n"
						       "}";

	const char* fragmentsource = "#version 330 core\n"
							 	 "uniform vec3 mycolor;\n"
						         "layout(location = 0) out vec3 color;\n"				
						         "void main() {\n"
								 "color = mycolor;\n"
						         "}";

	//for errors
	int success;
	char infoLog[512];

	//first: create shaders and link them to a program
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexsource, nullptr);
	glCompileShader(vertexshader);

	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentsource, nullptr);
	glCompileShader(fragmentshader);

	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexshader);
	glAttachShader(shaderprogram, fragmentshader);
	glLinkProgram(shaderprogram);

	glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderprogram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//second: create VAO and VBO and set data
	GLuint vertexobject;
	glGenVertexArrays(1, &vertexobject);

	GLuint bufferobject;
	glGenBuffers(1, &bufferobject);

	glBindVertexArray(vertexobject);
	glBindBuffer(GL_ARRAY_BUFFER, bufferobject);

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//now its time to draw, first triangle green, second purple
	this->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	glUseProgram(shaderprogram);
	GLint uniformlocation = glGetUniformLocation(shaderprogram, "mycolor");
	glUniform3f(uniformlocation, 0.443f, 0.694f, 0.153f);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUniform3f(uniformlocation, 0.567f, 0.306f, 0.847f);
	glDrawArrays(GL_TRIANGLES, 3, 6);
}

void Window::drawTetraeder() {
	glm::vec3 v1 = glm::vec3(-0.6, -0.6, 0.39);
	glm::vec3 v2 = glm::vec3(0.6, -0.6, 0.39);
	glm::vec3 v3 = glm::vec3(0.0, -0.6, -0.78);
	glm::vec3 v4 = glm::vec3(0.0, 0.6, 0.0);

	//normal vertices should be normalized and are pointing away from the triangleside
	glm::vec3 n1 = glm::cross((v3 - v1), (v2 - v1));
	n1 = n1 / glm::length(n1);
	glm::vec3 n2 = glm::cross((v3 - v2), (v4 - v2));
	n2 = n2 / glm::length(n2);
	glm::vec3 n3 = glm::cross((v1 - v3), (v4 - v3));
	n3 = n3 / glm::length(n3);
	glm::vec3 n4 = glm::cross((v1 - v4), (v2 - v4));
	n4 = n4 / glm::length(n4);

	//printf("%f  %f  %f\n", n1.x, n1.y, n1.z);
	//printf("%f  %f  %f\n", n2.x, n2.y, n2.z);
	//printf("%f  %f  %f\n", n3.x, n3.y, n3.z);
	//printf("%f  %f  %f\n", n4.x, n4.y, n4.z);

	//ground(n1), right(n2), left(n3), back(n4)
	glm::vec3 data[] = { v1,n1,v2,n1,v3,n1,
						 v2,n2,v3,n2,v4,n2,
						 v1,n3,v3,n3,v4,n3,
						 v1,n4,v2,n4,v4,n4 
					   };
	int angle = 00;
	float values[16] = {
		cos(angle * M_PI/180), 0, sin(angle * M_PI / 180), 0,
		0, 1, 0, 0,
		-1 * sin(angle * M_PI / 180), 0, cos(angle * M_PI / 180), 0,
		0, 0, 0, 1
	};
	glm::mat4 rotationY = glm::make_mat4(values);
	glm::mat4 inverseY = glm::inverseTranspose(rotationY);

	const char* vertexsource = "#version 330 core\n"
							   "uniform mat4 model_to_world_matrix;\n"
							   "uniform mat4 inverse_model_to_world_matrix;\n"
							   "layout(location = 0) in vec3 vertex_position;\n"
								"layout(location = 1) in vec3 normal_position;\n"
								"out vec4 vertex_normal_worldspace;\n"
							   "void main() {\n"
								"gl_Position = model_to_world_matrix * vec4((vertex_position), 1.0f);\n"
								"vertex_normal_worldspace = inverse_model_to_world_matrix * vec4((normal_position), 1.0f);\n"
							  /* "gl_Position.xyz = vertex_position;\n"
							   "gl_Position.w = 1.0;\n"*/
							   "}";

	const char* fragmentsource = "#version 330 core\n"
								 "in vec4 vertex_normal_worldspace;\n"
								 "uniform vec3 user_color;\n"
								 "layout(location = 0) out vec3 color;\n"
								 "void main() {\n"
								 "float nz = vertex_normal_worldspace.z\n;"
								 "float factor = 0.5 + 0.5 * abs(nz);\n"
								 "color = factor * user_color;\n"
								 // "color = user_color;\n"
								 "}";

	int success;
	char infoLog[512];

	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexsource, nullptr);
	glCompileShader(vertexshader);

	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentsource, nullptr);
	glCompileShader(fragmentshader);

	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexshader);
	glAttachShader(shaderprogram, fragmentshader);
	glLinkProgram(shaderprogram);

	glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderprogram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	GLuint vertexobject;
	glGenVertexArrays(1, &vertexobject);

	GLuint bufferobject;
	glGenBuffers(1, &bufferobject);

	glBindVertexArray(vertexobject);
	glBindBuffer(GL_ARRAY_BUFFER, bufferobject);

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	GLint size = sizeof(glm::vec3);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*size, nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2*size, &size);

	this->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	glUseProgram(shaderprogram);
	glEnable(GL_DEPTH_TEST);
	GLint uniformmatrixlocation = glGetUniformLocation(shaderprogram, "model_to_world_matrix");
	GLint inverse_uniformmatrixlocation = glGetUniformLocation(shaderprogram, "inverse_model_to_world_matrix");
		glUniformMatrix4fv(uniformmatrixlocation, 1, GL_FALSE, glm::value_ptr(rotationY));
		glUniformMatrix4fv(inverse_uniformmatrixlocation, 1, GL_FALSE, glm::value_ptr(inverseY));
		GLint uniformcolorlocation = glGetUniformLocation(shaderprogram, "user_color");
		glUniform3f(uniformcolorlocation, 0.443f, 0.694f, 0.153f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUniform3f(uniformcolorlocation, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glUniform3f(uniformcolorlocation, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 6, 3);
		glUniform3f(uniformcolorlocation, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 9, 3);

}