#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_s.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "..\..\out\particleSystem.h"
#include "..\..\out\helper.h"
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
GLFWwindow* window;
unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
Shader ourShader;
mat4 projection;
mat4 view;
particleSystem ps;

void initializeParticles() {
	for(int i = 0; i < 30; i++) {
		if(i % 2 == 0) {
			ps.createParticle(
				helper::generateRandom3Vector(vec2(-5.0f, 5.0f)), helper::generateRandom3Vector(vec2(-pi<float>(), pi<float>())), helper::generateRandom3Vector(vec2(0.0f, 3.0f)), helper::generateRandom4Vector(vec2(0.3f, 1.0f)),
				"C:/Users/John/Documents/LearnOpenGL-master/resources/textures/awesomeface.png");
		}
		else {
			ps.createParticle(
				helper::generateRandom3Vector(vec2(-5.0f, 5.0f)), helper::generateRandom3Vector(vec2(-pi<float>(), pi<float>())), helper::generateRandom3Vector(vec2(0.0f, 3.0f)), helper::generateRandom4Vector(vec2(0.3f, 1.0f)),
				"C:/Users/John/Documents/LearnOpenGL-master/resources/textures/window.png");
		}
	}
}

bool initialize() {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if(window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	view = lookAt(vec3(0, 0, -5), vec3(0, 0, 0), vec3(0, 1, 0));
	projection = perspective(radians(80.0f), float(SCR_WIDTH / SCR_HEIGHT), 1.0f, 400.0f);
	// build and compile our shader zprogram
	// ------------------------------------
	ourShader = Shader("C://Users//John//Documents//particleSystem//4.3.texture.vs", "C://Users//John//Documents//particleSystem//4.3.texture.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords (note that we changed them to 2.0f!)
		 1.0f,  1.0f, -0.0f,//   1.0f, 0.0f, 0.0f,  // 2.0f, 2.0f, // top right
		 1.0f, -1.0f, -0.0f,//   0.0f, 1.0f, 0.0f,  // 2.0f, 0.0f, // bottom right
		-1.0f, -1.0f, -0.0f,//   0.0f, 0.0f, 1.0f,  // 0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, -0.0f,//   1.0f, 1.0f, 0.0f,  // 0.0f, 2.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);
	initializeParticles();
}

void cleanup() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

void render() {
	// render
	// ------


	// render container
	ourShader.use();
	ps.render(ourShader.ID, view, projection);

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void update(const float dt) {
	ps.update(dt);
}

int main() {
	if(!initialize()) {
		return -1;
	}
	double prevTime = glfwGetTime();
	double currentTime = glfwGetTime();

	// render loop
	// -----------
	while(!glfwWindowShouldClose(window)) {
		prevTime = currentTime;
		currentTime = glfwGetTime();

		processInput(window);
		update(float(currentTime - prevTime));
		render();
	}

	cleanup();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}