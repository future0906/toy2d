#define GLEW_STATIC
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <shader.h>


#define CHECK_GL_ERROR_DEBUG() \
do {\
  GLenum __error = glGetError(); \
if (__error) {\
  printf("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
} \
} while (false)


int main(int argc, char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Failed create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed intialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	} 
  CHECK_GL_ERROR_DEBUG();
	glViewport(0, 0, 800, 600);

  Toy2D::Shader s;
  s.Initialize("normal.vsh", "normal.fsh");

	//int uniformLocation = glGetUniformLocation(shaderProgram, "customColor");
//	GLfloat vertices[] = {
//		-0.5f, -0.5f, 0.0f,
//		0.5f, -0.5f, 0.0f,
//		-0.0f, 0.5f, 0.0f,
//	};

//	GLfloat vertices[] = {
//		0.5f, 0.5f, 0.0f, // Top Right
//		0.5f, -0.5f, 0.0f, // Bottom Right
//		-0.5f, -0.5f, 0.0f, // Bottom Left
//		-0.5f, 0.5f, 0.0f // Top Left
//	};
//	GLuint indices[] = { // Note that we start from 0!
//		0, 1, 3, // First Triangle
//		1, 2, 3 // Second Triangle
//	};


	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Top Right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// Bottom Left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,// Top Left
	};
	GLuint indices_ta[] = { // Note that we start from 0!
		0, 1, 3, // First Triangle
    1, 2, 3,
	};


	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_ta), indices_ta, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint VAO = 0;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), nullptr);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), reinterpret_cast<void*>(sizeof(GLfloat) * 3));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(0);

  int count = 0;
	while (!glfwWindowShouldClose(window)) {
		count++;
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
    s.Use();
    glBindVertexArray(VAO);
		if ((count / 10) % 2 == 0) {
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		}
		else {
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<void*>(sizeof(GLfloat) * 3));
		}

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	return 1;
}