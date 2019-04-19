#include <GL/glew.h>
#include <algorithm>

#include <iostream>

#include "utils/viewport_utils.h"
#include "ui/bridge_window.h"
#include "model/bridge_model.h"

#include "model/aplication_configuration.h"

#define DEG2RAD 3.14159/180.0

BridgeWindow::BridgeWindow(std::shared_ptr<BridgeModel> bridge_model, std::shared_ptr<ApplicationConfiguration> application_configuration) {
	this->bridge_model = bridge_model;
	this->application_configuration = application_configuration;
}

void BridgeWindow::init() {

	std::array<double, 4> bounds = this->bridge_model->get_bounds();
	double scale_out_factor = this->bridge_model->get_prefered_scale_out_factor();
	std::array<int, 2> window_size = this->get_size();

	Viewport viewport = ViewportUtil::calculate_viewport(window_size[0], window_size[1], bounds[0], bounds[1], bounds[2], bounds[3], scale_out_factor);
	
	this->point_size = viewport.get_point_size();
	std::array<double, 4> viewport_matrix = viewport.get_viewport_matrix();
	std::array<double, 4> orhto_matrix = viewport.get_ortho_matrix();

	glViewport(viewport_matrix[0], viewport_matrix[1], viewport_matrix[2], viewport_matrix[3]);
	glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho(orhto_matrix[0], orhto_matrix[1], orhto_matrix[2], orhto_matrix[3], 0, 1); // essentially set coordinate system

	if (this->application_configuration->get_write_video_flag()) {
		std::string filename = "./";

		filename += this->get_title();

		std::replace(filename.begin(), filename.end(), ':', '-');

		filename += ".avi";

		std::cout << "Started writting video to '" << filename << "'" << std::endl;

		this->outputVideo.set(cv::VIDEOWRITER_PROP_QUALITY, 100.0);

		//int fourcc = CV_FOURCC('M', 'S', 'V', 'C'); //Microspoft Video 1;
		//int fourcc = CV_FOURCC('X', '2', '6', '4'); //Microspoft Video 1;
		int fourcc = CV_FOURCC('M', 'J', 'P', 'G'); 
		//int fourcc = -1;

		this->outputVideo.open(filename.c_str(), fourcc, 20.00f, cv::Size(window_size[0], window_size[1]), true);
	}
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

		if (junction.is_fixed()) {
			glColor3d(0.7, 0.7, 0.7);
		}
		else {
			glColor3d(1.0, 0.0, 0);
		}
		

		draw_circle(junction.get_x(), junction.get_y(), this->point_size*2);
	}
	
	if (this->application_configuration->get_write_video_flag()) {

		std::array<int, 2> window_size = this->get_size();

		int width = window_size[0];
		int height = window_size[1];

		cv::Mat pixels(height, width, CV_8UC3);
		glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data);
		cv::Mat cv_pixels(height, width, CV_8UC3);
		for (int y = 0; y < height; y++) for (int x = 0; x < width; x++)
		{
			cv_pixels.at<cv::Vec3b>(y, x)[2] = pixels.at<cv::Vec3b>(height - y - 1, x)[0];
			cv_pixels.at<cv::Vec3b>(y, x)[1] = pixels.at<cv::Vec3b>(height - y - 1, x)[1];
			cv_pixels.at<cv::Vec3b>(y, x)[0] = pixels.at<cv::Vec3b>(height - y - 1, x)[2];
		}

		this->outputVideo << cv_pixels;
	}
}

BridgeWindow::~BridgeWindow() {
	this->outputVideo.release();
}
