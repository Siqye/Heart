#include "window.hpp"
#include <cstring>
#include <exception>
#include <set>
#include <utility>
#include <vector>

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

			initVulkan();

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

	bool Window::initVulkan()
	{
		try {
			return createVkInstance()
				&& createVkSurface()
				&& pickVkPhysicalDevice()
				&& createVkDevice();
		}
		catch (const std::exception& e) {
			LOG_FATAL(e.what());
			return false;
		}
	}

	bool Window::createVkInstance()
	{
		vk::ApplicationInfo appInfo{};
		appInfo.pApplicationName = "Vulkan API";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Heart";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_1;

		uint32_t glfwExtCount = 0;
		const char** glfwExts = glfwGetRequiredInstanceExtensions(&glfwExtCount);
		if (!glfwExts) {
			LOG_FATAL("GLFW: Vulkan is not supported");
			return false;
		}
		std::vector<const char*> extensions(glfwExts, glfwExts + glfwExtCount);

		std::vector<const char*> layers;
#ifndef NDEBUG
		const char* validation = "VK_LAYER_KHRONOS_validation";
		for (auto& l : m_vkContext.enumerateInstanceLayerProperties()) {
			if (std::strcmp(l.layerName, validation) == 0) {
				layers.push_back(validation);
				break;
			}
		}
#endif

		vk::InstanceCreateInfo info{};
		info.pApplicationInfo = &appInfo;
		info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		info.ppEnabledExtensionNames = extensions.data();
		info.enabledLayerCount = static_cast<uint32_t>(layers.size());
		info.ppEnabledLayerNames = layers.data();

		m_vkInstance = std::make_unique<vk::raii::Instance>(m_vkContext, info);
		return true;
	}

	bool Window::createVkSurface()
	{
		VkSurfaceKHR rawSurface = VK_NULL_HANDLE;
		if (glfwCreateWindowSurface(static_cast<VkInstance>(**m_vkInstance),
			m_window, nullptr, &rawSurface) != VK_SUCCESS) {
			LOG_FATAL("Failed to create window surface");
			return false;
		}
		m_vkSurface = std::make_unique<vk::raii::SurfaceKHR>(*m_vkInstance, rawSurface);
		return true;
	}

	bool Window::pickVkPhysicalDevice()
	{
		vk::raii::PhysicalDevices devices(*m_vkInstance);
		if (devices.empty()) {
			LOG_FATAL("No Vulkan-capable GPU found");
			return false;
		}

		for (auto& dev : devices) {
			// нужна поддержка swapchain
			bool hasSwapchain = false;
			for (auto& ext : dev.enumerateDeviceExtensionProperties()) {
				if (std::strcmp(ext.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0) {
					hasSwapchain = true;
					break;
				}
			}
			if (!hasSwapchain) continue;

			auto families = dev.getQueueFamilyProperties();
			bool foundGraphics = false, foundPresent = false;
			for (uint32_t i = 0; i < families.size(); i++) {
				if (!foundGraphics && (families[i].queueFlags & vk::QueueFlagBits::eGraphics)) {
					m_graphicsFamily = i;
					foundGraphics = true;
				}
				if (!foundPresent && dev.getSurfaceSupportKHR(i, **m_vkSurface)) {
					m_presentFamily = i;
					foundPresent = true;
				}
			}

			if (foundGraphics && foundPresent) {
				m_vkPhysicalDevice = std::make_unique<vk::raii::PhysicalDevice>(std::move(dev));
				return true;
			}
		}

		LOG_FATAL("No suitable GPU found");
		return false;
	}

	bool Window::createVkDevice()
	{
		std::set<uint32_t> uniqueFamilies = { m_graphicsFamily, m_presentFamily };
		float priority = 1.0f;

		std::vector<vk::DeviceQueueCreateInfo> queueInfos;
		for (uint32_t family : uniqueFamilies) {
			vk::DeviceQueueCreateInfo q{};
			q.queueFamilyIndex = family;
			q.queueCount = 1;
			q.pQueuePriorities = &priority;
			queueInfos.push_back(q);
		}

		const char* deviceExts[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		vk::PhysicalDeviceFeatures features{};

		vk::DeviceCreateInfo info{};
		info.queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size());
		info.pQueueCreateInfos = queueInfos.data();
		info.enabledExtensionCount = 1;
		info.ppEnabledExtensionNames = deviceExts;
		info.pEnabledFeatures = &features;

		m_vkDevice = std::make_unique<vk::raii::Device>(*m_vkPhysicalDevice, info);
		m_vkGraphicsQueue = std::make_unique<vk::raii::Queue>(*m_vkDevice, m_graphicsFamily, 0);
		m_vkPresentQueue = std::make_unique<vk::raii::Queue>(*m_vkDevice, m_presentFamily, 0);
		return true;
	}
} } }