#include<gtest/gtest.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include<ui/gl_window.h>

namespace {

	class MockGlWindow : public GLWindow {
	protected:
		void init() {}
		void draw() {}
	};

	class GLWindowTest : public ::testing::Test {

	protected:
		void SetUp() {
			glewExperimental = true; // Needed for core profile
			glfwInit();
		}

		void TearDown() {
			glfwTerminate();
		}
	};

	TEST_F(GLWindowTest, general_flow_create_close)
	{
		MockGlWindow window;

		ASSERT_EQ(false, window.is_active());
		ASSERT_EQ(true, window.create());
		ASSERT_EQ(true, window.is_active());
		ASSERT_EQ(true, window.close());
		ASSERT_EQ(false, window.is_active());
	}

	TEST_F(GLWindowTest, first_close)
	{
		MockGlWindow window;

		ASSERT_EQ(false, window.close());
		ASSERT_EQ(true, window.create());
		ASSERT_EQ(true, window.is_active());
		ASSERT_EQ(true, window.close());
		ASSERT_EQ(false, window.is_active());
	}

	TEST_F(GLWindowTest, create_after_close)
	{
		MockGlWindow window;

		ASSERT_EQ(true, window.create());
		ASSERT_EQ(true, window.is_active());
		ASSERT_EQ(true, window.close());
		ASSERT_EQ(false, window.create());
		ASSERT_EQ(false, window.is_active());
	}

	TEST_F(GLWindowTest, double_calls)
	{
		MockGlWindow window;

		ASSERT_EQ(false, window.is_active());

		ASSERT_EQ(true, window.create());
		ASSERT_EQ(true, window.create());

		ASSERT_EQ(true, window.is_active());

		ASSERT_EQ(true, window.close());
		ASSERT_EQ(true, window.close());

		ASSERT_EQ(false, window.is_active());
	}

	TEST_F(GLWindowTest, loop_test)
	{
		MockGlWindow window;


		ASSERT_EQ(false, window.update());

		ASSERT_EQ(true, window.create());

		ASSERT_EQ(true, window.update());
		ASSERT_EQ(true, window.update());

		ASSERT_EQ(true, window.close());

		ASSERT_EQ(false, window.update());
	}

	TEST_F(GLWindowTest, test_properties)
	{
		MockGlWindow window;

		window.set_size({ 1, 2 });
		window.set_position({ 3, 4 });
		window.set_title("some_title");

		std::array<int, 2> expeced_size = { 1, 2 };
		std::array<int, 2> expeced_position = { 3, 4 };

		ASSERT_EQ(window.get_size(), expeced_size);
		ASSERT_EQ(window.get_position(), expeced_position);
		ASSERT_EQ(window.get_title(), "some_title");
	}
}
