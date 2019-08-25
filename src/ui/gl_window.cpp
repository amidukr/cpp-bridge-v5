#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "model/global_vars.h"
#include "ui/gl_window.h"

GLWindow::GLWindow()
{
}

GLWindow::~GLWindow() {
	close();
}

bool GLWindow::create() {
	if (this->window) {
		return this->active;
	}

	
	if(!GlobalVars::get_headless_mode_flag()) {
		glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

		// Open a window and create its OpenGL context
		this->window = glfwCreateWindow(this->size[0], this->size[1], this->title.c_str(), NULL, NULL);
		glfwSetWindowPos(this->window, this->position[0], this->position[1]);

		if (this->window == NULL) {
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			return false;
		}

		glfwMakeContextCurrent(this->window);
	}else{
		printf("mocking\n");
		this->window = (GLFWwindow*)-1;
	}	
	
	this->init();

	this->active = true;
	return true;
}

bool GLWindow::update() {
	if (!this->active) return false;

	if(!GlobalVars::get_headless_mode_flag()) {

		glfwMakeContextCurrent(this->window); // Initialize GLEW

		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);
	}

	this->draw();

	if(!GlobalVars::get_headless_mode_flag()) {
		glfwSwapBuffers(this->window);
		glfwPollEvents();

		return glfwGetKey(this->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(this->window) == 0;
	}

	return true;
}

bool GLWindow::close() {
	if (!this->window) {
		return false;
	}

	if (!this->active) {
		return true;
	}

	this->active = false;
	if(this->window != (GLFWwindow*)-1) {
		glfwDestroyWindow(this->window);
	}

	return true;
}

bool GLWindow::is_active() {
	return this->active;
}

void GLWindow::set_position(std::array<int, 2> position) {
	this->position = position;
}

std::array<int, 2> GLWindow::get_position() {
	return this->position;
}

void GLWindow::set_size(std::array<int, 2> size) {
	this->size = size;
}

std::array<int, 2> GLWindow::get_size() {
	return this->size;
}

void GLWindow::set_title(std::string title) {
	this->title = title;
}

const std::string& GLWindow::get_title() {
	return this->title;
}
