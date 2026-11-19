#include <vector>
#include "colidebox.hpp"
#include <memory>

namespace heartCore { namespace physics {

	class PhysLayer {
	private:
		std::vector<std::shared_ptr<ColideBox2d>> m_objects;
		std::vector<std::shared_ptr<ColideBox2d>> m_potential;
		float m_gravityAcceleration;
		maths::vec2 m_gravityDirection;
	public:
		PhysLayer();
		~PhysLayer();

		void checkPotential();
		void calculatePotential();
		void addObject(std::shared_ptr<ColideBox2d> object);

		void update();
	};

} }