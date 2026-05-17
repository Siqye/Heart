
#include <glew.h>
#include <glfw3.h>
#include <iostream>

#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 32


namespace heartCore { namespace graphics {
	class Window
	{
	public:
		Window(int width, int height, const char* title);
		~Window();
		void clear() const;
		void update() const;
		bool close();
		bool isKeyPressed(int keycode) const;
		bool isMouseButtonPressed(int button) const;
		void getMousePosition(double& x, double& y) const;

	private:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		bool init();
		

		bool m_closed;
		int m_width, m_height;
		double m_mouseX, m_mouseY;
		const char* m_title;
		bool m_keyboardArrayKeys[MAX_KEYS], m_mouseArrayButtons[MAX_MOUSE_BUTTONS];
		GLFWwindow* m_window;
	};
} }