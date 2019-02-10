#include <GL/glew.h>

#include "ui/bridge_window.h"
#include "model/bridge_model.h"

BridgeWindow::BridgeWindow(std::shared_ptr<BridgeModel> bridge_model) {
	this->bridge_model = bridge_model;
}

void BridgeWindow::draw() {
	/*auto bridge_model = this->bridge_model;
	for (int i = 0; i < bridge_model->get_girder_len(); i++) {
		auto girder = this->bridge_model->get_girder(i);
		auto junction1 = this->bridge_model->get_girder();
	}*/
	glClearColor(0.0, 1.0, 0, 0);
	// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
	glClear(GL_COLOR_BUFFER_BIT);
}
