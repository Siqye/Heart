#include "../maths/maths.hpp"
#include "physlayer.hpp"

// matches lenght between vertecies to mark them as potential colide
#define POTENTIAL_CONSTANT_FLOAT 3.0f
#define POTENTIAL_CONSTANT_DOUBLE 3.0


namespace heartCore { namespace physics {
	class ColideManager2d {
	private:
		std::vector<PhysLayer> layers;

		void checkPotential();
		void calculatePotential();
	public:
		ColideManager2d(int reserveLayers);
		~ColideManager2d();

		void update();
	};
} }