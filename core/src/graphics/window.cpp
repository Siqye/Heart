#include "window.hpp"

namespace heartCore { namespace graphics {

	Window::Window(int width, int height, const char* title) 
		: m_width(width), m_height(height), m_title(title)
	{
		m_closed = !init();
		m_mouseX = 0.0;
		m_mouseY = 0.0;
		for (int i = 0; i < MAX_KEYS; i++) {
			m_keyboardArrayKeys[i] = false;
		}
		for (int i = 0; i < MAX_MOUSE_BUTTONS; i++) {
			m_mouseArrayButtons[i] = false;
		}
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Window::clear() const
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::update() const
	{
		glViewport(0, 0, m_width, m_height);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	bool Window::close()
	{
		m_closed = glfwWindowShouldClose(m_window);
		return !m_closed;
	}
	bool Window::init()
	{
		if (!glfwInit()) 
		{
			std::cout << "Failed to initialize GLFW" << std::endl;
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

		if (!m_window) {
			std::cout << "Failed to create window" << std::endl;
			return false;
		}

		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);

		
		glfwMakeContextCurrent(m_window);

		if (glewInit() != GLEW_OK) {
			std::cout << "Failed to initialize GLEW" << std::endl;
			return false;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}

	void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_keyboardArrayKeys[key] = action != GLFW_RELEASE;
		
	}

	void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_mouseArrayButtons[button] = action != GLFW_RELEASE;
		
	}

	bool Window::isKeyPressed(int keycode) const {
		if (keycode >= MAX_KEYS) return false;
		return m_keyboardArrayKeys[keycode];
	}
	bool Window::isMouseButtonPressed(int button) const {
		if (button >= MAX_MOUSE_BUTTONS) return false;
		return m_mouseArrayButtons[button];
	}
	void Window::getMousePosition(double& x, double& y) const {
		x = m_mouseX;
		y = m_mouseY;
	}

	void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_mouseX = xpos;
		win->m_mouseY = ypos;
	}
} }