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

void Window::swapColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(window_);
}

void Window::createTriangles() {
	//some examples of vec3
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
						         "layout(location = 0) out vec3 color;\n"
								 "uniform vec3 mycolor; \n"					
						         "void main() {\n"
								 //"color = vec3(0.443, 0.694, 0.153);\n"
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	//now its time to draw
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderprogram);
	//first triangle green, second purple
	GLint uniformlocation = glGetUniformLocation(shaderprogram, "mycolor");
	glUniform3f(uniformlocation, 0.443f, 0.694f, 0.153f);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUniform3f(uniformlocation, 0.567f, 0.306f, 0.847f);
	glDrawArrays(GL_TRIANGLES, 3, 6);

	SDL_GL_SwapWindow(window_);
}