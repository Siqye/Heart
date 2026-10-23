#include "../graphics/staticsprite.hpp"
#include "../physics/colidebox.hpp"


namespace heartCore {
	class Entity2d {
	private:
		maths::vec3* m_position;
		maths::vec3* m_size;

		graphics::StaticSprite* m_visualisation;
		physics::ColideBox2d* m_hitBox;

	public:
		Entity2d(graphics::StaticSprite* visual, physics::ColideBox2d* hitBox);

		void update();
	};
}