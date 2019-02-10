#include <GL/glew.h>
#include <algorithm>

#include "ui/bridge_window.h"
#include "model/entity/junction.h"
#include "model/bridge_model.h"

#define DEG2RAD 3.14159/180.0

BridgeWindow::BridgeWindow(std::shared_ptr<BridgeModel> bridge_model) {
	this->bridge_model = bridge_model;
}

void BridgeWindow::init() {
	double SCREEN_WIDTH = 640;
	double SCREEN_HEIGHT = 480;

	auto bounds = this->bridge_model->get_bounds();

	double width = bounds[2] - bounds[0];
	double height = bounds[3] - bounds[1];

	double max_size = std::max(width, height);
	std::array<double, 2> center = { (bounds[0] + bounds[2]) / 2.0,
						 (bounds[1] + bounds[3]) / 2.0, };

	this->point_size = max_size / 100;

	std::array<double, 4> screen = { center[0] - max_size,
									 center[1] - max_size,
									 center[0] + max_size,
									 center[1] + max_size};

	std::array<double, 2> window_size = this->get_size();
	

	double window_min_dimension = std::min(window_size[0], window_size[1]);

	std::array<double, 2> viewport_shift;
	double viewport_shift_offset = std::abs(window_size[0] - window_size[1])/2;

	
	if (window_size[0] > window_size[1]) {
		viewport_shift = { viewport_shift_offset, 0 };
	} else {
		viewport_shift = { 0, viewport_shift_offset };
	};

	glViewport(viewport_shift[0], viewport_shift[1], window_min_dimension, window_min_dimension);
	glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho(screen[0], screen[2] , screen[1] , screen[3] , 0, 1); // essentially set coordinate system
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
