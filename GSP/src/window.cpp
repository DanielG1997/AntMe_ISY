#include "window.hpp"

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

  //create VBO and VAO
  glGenVertexArrays(1, &vertexobject);
  glGenBuffers(1, &bufferobject);

  glBindVertexArray(vertexobject);
  glBindBuffer(GL_ARRAY_BUFFER, bufferobject);
}

void Window::setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	glClearColor(red, green, blue, alpha);
}

void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap() {
	SDL_GL_SwapWindow(window_);
}

GLuint Window::createProgramWithShaders(const char* vertexsource, const char* fragmentsource) {
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

void Window::deleteShaderObjects() {
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	glDeleteProgram(shaderprogram);
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

	GLuint shaderprogram = this->createProgramWithShaders(vertexsource, fragmentsource);

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//now its time to draw, first triangle green, second purple
	GLint uniformlocation = glGetUniformLocation(shaderprogram, "mycolor");
	glUniform3f(uniformlocation, 0.443f, 0.694f, 0.153f);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUniform3f(uniformlocation, 0.567f, 0.306f, 0.847f);
	glDrawArrays(GL_TRIANGLES, 3, 3);

	this->deleteShaderObjects();
}


void Window::drawTetrahedron(float degrees) {
	glm::vec3 v0 = glm::vec3(-0.6, -0.6, 0.39);
	glm::vec3 v1 = glm::vec3(0.6, -0.6, 0.39);
	glm::vec3 v2 = glm::vec3(0.0, -0.6, -0.78);
	glm::vec3 v3 = glm::vec3(0.0, 0.6, 0.0);

	//normal vertices should be normalized and are pointing away from the triangleside
	glm::vec3 n0 = glm::cross((v2 - v0), (v1 - v0));
	n0 = n0 / glm::length(n0);
	glm::vec3 n1 = glm::cross((v2 - v1), (v3 - v1));
	n1 = n1 / glm::length(n1);
	glm::vec3 n2 = glm::cross((v0 - v2), (v3 - v2));
	n2 = n2 / glm::length(n2);
	glm::vec3 n3 = glm::cross((v0 - v3), (v1 - v3));
	n3 = n3 / glm::length(n3);

	//printf("%f %f %f\n", n0.x, n0.y, n0.z);
	//printf("%f %f %f\n", n1.x, n1.y, n1.z);
	//printf("%f %f %f\n", n2.x, n2.y, n2.z);
	//printf("%f %f %f\n", n3.x, n3.y, n3.z);

	//ground(n0), right(n1), left(n2), back(n3)
	glm::vec3 data[] = { v0,n0,v1,n0,v2,n0,
						 v1,n1,v2,n1,v3,n1,
						 v0,n2,v2,n2,v3,n2,
						 v0,n3,v1,n3,v3,n3
	};


	//operations todo
	glm::mat4x4 rotationX = this->getRotationMatrix('x', degrees);
	glm::mat4x4 rotationY = this->getRotationMatrix('y', degrees);
	glm::mat4x4 rotationZ = this->getRotationMatrix('z', degrees);

	glm::mat4x4 operations = rotationY;

	const char* vertexsource =  "#version 330 core\n"
							    "uniform mat4 model_to_world_matrix;\n"
								"layout(location = 0) in vec3 vertex_position;\n"
								"layout(location = 1) in vec3 normal_position;\n"
								"out vec3 vertex_normal_worldspace;\n"
								"void main() {\n"
								"gl_Position = model_to_world_matrix * vec4((vertex_position), 1.0f);\n"
								"vertex_normal_worldspace = (transpose(inverse(model_to_world_matrix)) * vec4((normal_position), 0.0)).xyz;\n"
								"}";

	const char* fragmentsource = "#version 330 core\n"
								 "in vec3 vertex_normal_worldspace;\n"
								 "uniform vec3 user_color;\n"
								 "layout(location = 0) out vec3 color;\n"
								 "void main() {\n"
								 "float nz = vertex_normal_worldspace.z;\n"
								 "float factor = 0.5 + 0.5 * abs(nz);\n"
								 "color = factor * user_color;\n"
								 "}";

	GLuint shaderprogram = this->createProgramWithShaders(vertexsource, fragmentsource);

	GLint size = sizeof(glm::vec3);

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*size, nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2*size, (void*)size);

	glEnable(GL_DEPTH_TEST);
	GLint uniformmatrixlocation = glGetUniformLocation(shaderprogram, "model_to_world_matrix");
	glUniformMatrix4fv(uniformmatrixlocation, 1, GL_TRUE, glm::value_ptr(operations));
	GLint uniformcolorlocation = glGetUniformLocation(shaderprogram, "user_color");
	glUniform3f(uniformcolorlocation, 0.443f, 0.694f, 0.153f);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUniform3f(uniformcolorlocation, 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 3, 3);
	glUniform3f(uniformcolorlocation, 0.0f, 1.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 6, 3);
	glUniform3f(uniformcolorlocation, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 9, 3);

	this->deleteShaderObjects();
}