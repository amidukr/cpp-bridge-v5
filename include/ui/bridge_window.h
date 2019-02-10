#ifndef BRIDGE_WINDOW_H
#define BRIDGE_WINDOW_H

#include <memory>
#include "ui/gl_window.h"

class BridgeModel;

class BridgeWindow :
	public GLWindow
{
	std::shared_ptr<BridgeModel> bridge_model;
	double point_size = 0;
public:
	BridgeWindow(std::shared_ptr<BridgeModel> bridge_model);
protected:
	void init();
	void draw();
};

#endif /*BRIDGE_WINDOW_H*/
