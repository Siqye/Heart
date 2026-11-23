#pragma once
#include "entity2d.hpp"
#include "camera2d.hpp"
#include "../graphics/API/window.hpp"
#include "../physics/boxmanager.hpp"
#include "../graphics/layers/levellayer.hpp"
#include <vector>

namespace heartCore {

	class Scene2d {
	protected:
		std::vector<Entity2d*> m_objects;
		Camera2d m_camera;
		std::shared_ptr<graphics::API::Shader> m_shader;
		graphics::API::Window* m_window;
		
		graphics::LevelLayer m_graphicLayer;
		physics::ColideManager2d m_physManager;
		
	public:
		Scene2d(graphics::API::Window* window);

		void addObject(Entity2d* entity);
	

		virtual void update() = 0;
		virtual void tick() = 0;
		virtual void render() = 0;
	};

}