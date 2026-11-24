#include "window.hpp"
#include "../../logger/logger.hpp"

namespace heartCore { namespace graphics {
namespace API {

	Window::Window(int width, int height, const char* title, RenderAPI api)
		: m_width(width), m_height(height), m_title(title), m_renderAPI(api)
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
		switch (m_renderAPI) {
		case RenderAPI::OpenGL:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		case RenderAPI::Vulkan:
			return;
		case RenderAPI::DirectX:
			return;
		}
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
		switch (m_renderAPI) {
		case RenderAPI::OpenGL:
			if (!glfwInit())
			{
				LOG_FATAL("GLFW initialization error");
				return false;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

			if (!m_window) {
				LOG_FATAL("Failed to create window");
				return false;
			}

			glfwSetWindowUserPointer(m_window, this);
			glfwSetKeyCallback(m_window, key_callback);
			glfwSetMouseButtonCallback(m_window, mouse_button_callback);
			glfwSetCursorPosCallback(m_window, cursor_position_callback);


			glfwMakeContextCurrent(m_window);

			if (glewInit() != GLEW_OK) {
				LOG_FATAL("Failed to initalaze GLEW");
				return false;
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			return true;

		case RenderAPI::Vulkan:

			if (!glfwInit()) {
				LOG_FATAL("GLFW initialization error");
				return false;
			}
			
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

			m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

			if (!m_window) {
				LOG_FATAL("GLFW: failed to create window");
				return false;
			}

			VkApplicationInfo appInfo;
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Vulkan API";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			VkInstanceCreateInfo instanceInfo;
			instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceInfo.pApplicationInfo = &appInfo;
			instanceInfo.enabledExtensionCount = 0;
			instanceInfo.ppEnabledExtensionNames = nullptr;
			instanceInfo.enabledLayerCount = 0;
			instanceInfo.ppEnabledLayerNames = nullptr;

			if (!vkCreateInstance(&instanceInfo, nullptr, &m_vkInstance)) {
				LOG_FATAL("Vulkan initialisation failed!");
				return false;
			}

			createVkSurface();

			if (glfwCreateWindowSurface(m_vkInstance, m_window, nullptr, &m_surface)) {
				LOG_FATAL("Failed to initialize vulkan surface");
				return false;
			}

			return true;

		case RenderAPI::DirectX:
			return false;
		}
		
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

	void Window::createVkSurface() {
		VkSurfaceKHR       _surface;
		if (glfwCreateWindowSurface(m_vkInstance, m_window, nullptr, &_surface) != 0) {
			LOG_FATAL("failed to create window surface!");
		}
		m_vkSurface = vk::raii::SurfaceKHR(,)
	}

} } }