#ifndef GL_WINDOW_H
#define GL_WINDOW_H

struct GLFWwindow;

class GLWindow
{
	GLFWwindow* window = 0;
	bool active = false;

protected:
	virtual void init() = 0;
	virtual void draw() = 0;
	

public:
	GLWindow();

	bool is_active();
	bool create();
	bool loop();
	bool close();

	virtual ~GLWindow();

private:
	// Disable copy constructor
	GLWindow(const GLWindow&); // no implementation 
	GLWindow& operator=(const GLWindow&); // no implementation 
};

#endif /*GL_WINDOW_H*/
