#pragma once
#include <glew.h>
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>
#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>
#include <iostream>
#include <set>
#include <cstring>
#include "../../logger/logger.hpp"

#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 32
//
namespace heartCore { namespace graphics {
namespace API {

	enum class RenderAPI {
		OpenGL,
		Vulkan,
		DirectX
	};

	class Window {
	private:
		GLFWwindow* m_window;
		const char* m_title;
		
		bool m_closed;
		int m_width, m_height;
		double m_mouseX, m_mouseY;
		
		bool m_keyboardArrayKeys[MAX_KEYS], m_mouseArrayButtons[MAX_MOUSE_BUTTONS];
		RenderAPI m_renderAPI;

		// vulkan stuff
		vk::raii::Context m_vkContext;

		std::unique_ptr<vk::raii::Instance> m_vkInstance;
		std::unique_ptr<vk::raii::DebugUtilsMessengerEXT> m_vkDebugMessenger;
		std::unique_ptr<vk::raii::SurfaceKHR> m_vkSurface;
		std::unique_ptr<vk::raii::PhysicalDevice> m_vkPhysicalDevice;
		std::unique_ptr<vk::raii::Device> m_vkDevice;
		std::unique_ptr<vk::raii::Queue> m_vkGraphicsQueue;
		std::unique_ptr<vk::raii::Queue> m_vkPresentQueue;

		std::uint32_t m_graphicsFamily = 0;
		std::uint32_t m_presentFamily = 0;

	public:
		Window(int width, int height, const char* title, RenderAPI api);
		~Window();
		void clear() const;
		void update() const;
		bool close();

		bool isKeyPressed(int keycode) const;
		bool isMouseButtonPressed(int button) const;
		void getMousePosition(double& x, double& y) const;

		inline const RenderAPI& getRenderAPI() { return m_renderAPI; }

	private:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		bool init();

		//vk::SurfaceFormatKHR vkChooseSwapFormat(std::vector<vk::SurfaceFormatKHR> const& avaibleFormats);
		
		bool initVulkan();
		bool createVkInstance();
		bool createVkSurface();
		bool pickVkPhysicalDevice();
		bool createVkDevice();
	};
} } }
