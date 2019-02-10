#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <array>

struct GLFWwindow;

class GLWindow
{
	GLFWwindow* window = 0;
	bool active = false;

	std::array<int, 2> position = { 100, 100 };
	std::array<int, 2> size = { 1024, 768 };

protected:
	virtual void init() = 0;
	virtual void draw() = 0;
	

public:
	GLWindow();

	void set_position(std::array<int, 2> position);
	std::array<int, 2> get_position();

	void set_size(std::array<int, 2> size);
	std::array<int, 2> get_size();

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
