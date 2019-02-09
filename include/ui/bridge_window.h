#ifndef BRIDGE_WINDOW_H
#define BRIDGE_WINDOW_H

#include "ui/gl_window.h"

class BridgeWindow :
	public GLWindow
{
protected:
	void draw();
};

#endif /*BRIDGE_WINDOW_H*/