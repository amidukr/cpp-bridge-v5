#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "ui/bridge_window.h"

GLWindow::GLWindow() {

}

GLWindow::~GLWindow() {
	close();
}

bool GLWindow::create() {
	if (this->window) {
		return this->active;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	this->window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (this->window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return false;
	}

	this->active = true;
	return true;
}

bool GLWindow::loop() {
	if (!this->active) return false;

	glfwMakeContextCurrent(this->window); // Initialize GLEW

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);

	this->draw();

	glfwSwapBuffers(this->window);
	glfwPollEvents();

	return glfwGetKey(this->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(this->window) == 0;
}

bool GLWindow::close() {
	if (!this->window) {
		return false;
	}

	if (!this->active) {
		return true;
	}

	this->active = false;
	glfwDestroyWindow(this->window);
	return true;
}

bool GLWindow::is_active() {
	return this->active;
}

