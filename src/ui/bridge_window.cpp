#include <GL/glew.h>
#include <memory>

#include "ui/bridge_window.h"
#include "model/bridge_model.h"

std::unique_ptr<BridgeModel> create_bridge() {
	std::unique_ptr<BridgeModel> bridge_model;

	auto junction_bl = bridge_model->add_junction(20, 20);
	auto junction_br = bridge_model->add_junction(40, 20);
	auto junction_tl = bridge_model->add_junction(20, 40);
	auto junction_tr = bridge_model->add_junction(40, 40);

	bridge_model->add_girder(junction_bl, junction_br);
	bridge_model->add_girder(junction_br, junction_tr);
	bridge_model->add_girder(junction_tl, junction_tr);
	bridge_model->add_girder(junction_tl, junction_bl);

	return bridge_model;
}

void BridgeWindow::draw() {
	glClearColor(0.0, 1.0, 0, 0);
	// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
	glClear(GL_COLOR_BUFFER_BIT);
}
