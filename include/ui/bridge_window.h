#ifndef BRIDGE_WINDOW_H
#define BRIDGE_WINDOW_H

#include <memory>
#include "ui/gl_window.h"

#include "opencv2/opencv.hpp"

class BridgeModel;
class ApplicationConfiguration;

class BridgeWindow :
	public GLWindow
{
	std::shared_ptr<BridgeModel> bridge_model;
	double point_size = 0;

	cv::VideoWriter outputVideo;
	std::shared_ptr<ApplicationConfiguration> application_configuration;

public:
	BridgeWindow(std::shared_ptr<BridgeModel> bridge_model, std::shared_ptr<ApplicationConfiguration> application_configuration);
	~BridgeWindow();

protected:
	void init();
	void draw();
};

#endif /*BRIDGE_WINDOW_H*/
