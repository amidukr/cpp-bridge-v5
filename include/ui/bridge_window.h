#ifndef BRIDGE_WINDOW_H
#define BRIDGE_WINDOW_H

#include <memory>
#include "ui/gl_window.h"

#include <opencv\cv.h>
#include "opencv2\opencv.hpp"

class BridgeModel;

class BridgeWindow :
	public GLWindow
{
	std::shared_ptr<BridgeModel> bridge_model;
	double point_size = 0;

	cv::VideoWriter outputVideo;

public:
	BridgeWindow(std::shared_ptr<BridgeModel> bridge_model);
	~BridgeWindow();

protected:
	void init();
	void draw();
};

#endif /*BRIDGE_WINDOW_H*/
