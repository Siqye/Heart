#pragma once
#include <glew.h>
#include "vulkancontext.hpp"
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

		VulkanContext m_vkContext;

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
	};
} } }
