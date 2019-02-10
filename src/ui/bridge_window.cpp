#include <GL/glew.h>
#include <algorithm>

#include "utils/viewport_utils.h"
#include "ui/bridge_window.h"
#include "model/bridge_model.h"

#define DEG2RAD 3.14159/180.0

BridgeWindow::BridgeWindow(std::shared_ptr<BridgeModel> bridge_model) {
	this->bridge_model = bridge_model;
}

void BridgeWindow::init() {

	std::array<double, 4> bounds = this->bridge_model->get_bounds();
	double scale_out_factor = this->bridge_model->get_prefered_scale_out_factor();
	std::array<double, 2> window_size = this->get_size();

	Viewport viewport = ViewportUtil::calculate_viewport(window_size[0], window_size[1], bounds[0], bounds[1], bounds[2], bounds[3], scale_out_factor);
	
	this->point_size = viewport.get_point_size();
	std::array<double, 4> viewport_matrix = viewport.get_viewport_matrix();
	std::array<double, 4> orhto_matrix = viewport.get_ortho_matrix();

	glViewport(viewport_matrix[0], viewport_matrix[1], viewport_matrix[2], viewport_matrix[3]);
	glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho(orhto_matrix[0], orhto_matrix[1], orhto_matrix[2], orhto_matrix[3], 0, 1); // essentially set coordinate system
}

void draw_circle(float x, float y, float radius)
{
	int i;

	glBegin(GL_POLYGON);

	for (i = 0; i < 360; i++)
	{
		float rad = i * DEG2RAD;
		glVertex2f(x + cos(rad)*radius,
			       y + sin(rad)*radius);
	}

	glEnd();
}

void BridgeWindow::draw() {
	BridgeModel& bridge_model = *this->bridge_model;

	glClearColor(0.0, 1.0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(5);
	glColor3d(1.0, 1.0, 0);
	
	glBegin(GL_LINES);
	for (int i = 0; i < bridge_model.get_girder_len(); i++) {
		Girder& girder = bridge_model.get_girder(i);
		
		Junction& junction1 = bridge_model.get_junction(girder.get_junction1_id());
		Junction& junction2 = bridge_model.get_junction(girder.get_junction2_id());

		glVertex2dv(junction1.get_coordinate().data());
		glVertex2dv(junction2.get_coordinate().data());
	}

	glEnd();

	

	for (int i = 0; i < bridge_model.get_junctions_len(); i++) {
		Junction& junction = bridge_model.get_junction(i);

		if (junction.is_hard()) {
			glColor3d(0.7, 0.7, 0.7);
		}
		else {
			glColor3d(1.0, 0.0, 0);
		}
		

		draw_circle(junction.get_x(), junction.get_y(), this->point_size*2);
	}
}
