#include "entity2d.hpp"
#include "camera2d.hpp"

#include <vector>


namespace heartCore {

	class Scene2d {
	private:
		std::vector<Entity2d*> m_objects;
		Camera2d m_camera;
		
	public:
		Scene2d();

		void update();
		void tick();
		void render();
	};

}