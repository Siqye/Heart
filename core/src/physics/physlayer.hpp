#include <vector>
#include "colidebox.hpp"

namespace heartCore { namespace physics {

	class PhysLayer {
	private:
		std::vector<ColideBox2d*> m_objects;
		std::vector<ColideBox2d*> m_potential;
		float m_gravityAcceleration;
		maths::vec2 m_gravityDirection;
	public:
		PhysLayer(float gravityAcceleration = 10.0f, maths::vec2 gravityDirection = maths::vec2());
		~PhysLayer();

		void checkPotential();
		void calculatePotential();
		void addObject(ColideBox2d* object);

		void update();
	};

} }