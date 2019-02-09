#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <memory>
#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "ui/bridge_window.h"

void create_windows() {
	BridgeWindow bridge_window;
	
	bridge_window.create();

	while (bridge_window.loop());
}

int main(int argc, char* argv[]) {

	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	create_windows();

	glfwTerminate();
	
	return 0;
}