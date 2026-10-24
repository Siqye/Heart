#pragma once
#include "entity2d.hpp"
#include "camera2d.hpp"
#include "../graphics/window.hpp"
#include "../physics/boxmanager.hpp"
#include "../graphics/layers/levellayer.hpp"
#include <vector>

namespace heartCore {

	class Scene2d {
	protected:
		std::vector<Entity2d*> m_objects;
		Camera2d m_camera;
		graphics::Shader* m_shader;
		graphics::Window* m_window;
		
		graphics::LevelLayer m_graphicLayer;
		physics::ColideManager2d m_physManager;
		
	public:
		Scene2d(graphics::Window* window);

		void addObject(Entity2d* entity);
	

		virtual void update() = 0;
		virtual void tick() = 0;
		virtual void render() = 0;
	};

}