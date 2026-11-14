#include "boxmanager.hpp"

namespace heartCore { namespace physics {
	ColideManager2d::ColideManager2d() {
	}

	ColideManager2d::~ColideManager2d() { }

	void ColideManager2d::checkPotential() {
		for (int i = 0; i < layers.size(); i++) {
			layers[i]->checkPotential();
		}
	}

	void ColideManager2d::calculatePotential() {
		for (int i = 0; i < layers.size(); i++) {
			layers[i]->calculatePotential();
		}
	}

	void ColideManager2d::updateObjects() {
		for (int i = 0; i < layers.size(); i++) {
			layers[i]->update();
		}
	}

	void ColideManager2d::update() {
		checkPotential();
		updateObjects();
		calculatePotential();
	}


	void ColideManager2d::addLayer(PhysLayer* layer) {
		layers.push_back(layer);
	}

	void ColideManager2d::addBox(ColideBox2d* object, int layerID) {
		layers[layerID]->addObject(object);
	}

} }