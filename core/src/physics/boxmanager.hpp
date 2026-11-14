#include "../maths/maths.hpp"
#include "physlayer.hpp"

// matches lenght between vertecies to mark them as potential colide
#define POTENTIAL_CONSTANT_FLOAT 3.0f
#define POTENTIAL_CONSTANT_DOUBLE 3.0


namespace heartCore { namespace physics {
	class ColideManager2d {
	private:
		std::vector<PhysLayer*> layers;

		void checkPotential();
		void calculatePotential();
		void updateObjects();
	public:
		ColideManager2d();
		~ColideManager2d();

		void addLayer(PhysLayer* layer = new PhysLayer);
		void addBox(ColideBox2d* object, int layerID = 0);
		void update();
	};
} }