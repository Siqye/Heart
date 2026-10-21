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
		PhysLayer(float gravityAcceleration, maths::vec2 gravityDirection);
		~PhysLayer();

		void checkPotential();
		void calculatePotential();
	};

} }