#pragma once
#include <glew.h>
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>
#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>
#include <iostream>

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

		VkInstance m_vkInstance;
		vk::raii::SurfaceKHR m_vkSurface;

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

		vk::SurfaceFormatKHR vkChooseSwapFormat(std::vector<vk::SurfaceFormatKHR> const& avaibleFormats);

		void createVkSurface();
	};
} } }
