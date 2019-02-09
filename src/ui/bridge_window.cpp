#include <GL/glew.h>

#include "ui/bridge_window.h"

void BridgeWindow::draw() {
	glClearColor(0.0, 1.0, 0, 0);
	// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
	glClear(GL_COLOR_BUFFER_BIT);
}
