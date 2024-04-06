#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <learnopengl/filesystem.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "..\..\out\particleSystem.h"
#include "..\..\out\particleEmitter.h"
#include "..\..\out\helper.h"
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
GLFWwindow* window;
mat4 projection;
mat4 view;
particleSystem ps;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		ps.toggleEmitter("smoke");
	else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		ps.oneTimeEmit("smoke", 10);
}
void initializeParticles() {
	std::vector<std::string> textures = { "C:/Users/John/Source/Repos/openGLTest/openGLTest/resources/particles/smoke.png", "C:/Users/John/Source/Repos/openGLTest/openGLTest/resources/particles/smoke_01.png", "C:/Users/John/Source/Repos/openGLTest/openGLTest/resources/particles/smoke2.png" };
	particleEmitter temp("smoke", 100, 1, vec2(0, 2),
		//pos
		vec3(0, -2, 0), vec2(-.1, .1), vec2(0, .3), vec2(-.1, .1),
		//vel
		vec3(0, 0.1, 0), vec2(-0.1, 0.2), vec2(-0.1, 1.5), vec2(-0.1, 0.2),
		//acl
		vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0),
		//ori
		vec3(0, 0, 0), vec2(0, 0), vec2(0, 0), vec2(0, 0),
		//ori rate
		vec3(0, 0, 0), vec2(-.1, .1), vec2(-.1, .1), vec2(-.1, .1),
		//scale
		vec3(0.6, 0.6, 0.6), vec2(-0.2, 0.2), vec2(-0.2, 0.2), vec2(-0.2, 0.2),
		//scale rate
		vec3(0.1, 0.1, 0.1), vec2(-.1, 0.3), vec2(-.1, 0.3), vec2(-.1, 0.3),
		//start colour
		vec4(1, 1, 1, 1), vec2(-.1, .1), vec2(-.1, .1), vec2(-.1, .1), vec2(-.1, .1),
		//end colour
		vec4(0.3, 0.3, 0.3, 0.2), vec2(-.1, .1), vec2(-.1, .1), vec2(-.1, .1), vec2(-.1, .1)
		//life span
		, 5, vec2(-2, 5)
		//textures
		, textures);
	ps.addEmitter(temp);
	ps.enableEmitter("smoke");
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
	glfwSetKeyCallback(window, key_callback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	if(!ps.initialize()) {
		return false;
	}
	view = lookAt(vec3(0, 0, -5), vec3(0, 0, 0), vec3(0, 1, 0));
	projection = perspective(radians(80.0f), float(SCR_WIDTH / SCR_HEIGHT), 1.0f, 400.0f);
	initializeParticles();
	return true;
}

void cleanup() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	ps.cleanup();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

void render() {
	// render
	// ------


	// render container
	ps.render(view, projection);

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

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}