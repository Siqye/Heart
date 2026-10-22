#include "boxmanager.hpp"

namespace heartCore { namespace physics {
	ColideManager2d::ColideManager2d(int reserveLayers = 0) {
		if (reserveLayers == 0) return;
		layers.reserve(reserveLayers);
	}

	ColideManager2d::~ColideManager2d() { }

	void ColideManager2d::checkPotential() {
		for (int i = 0; i < layers.size(); i++) {
			layers[i].checkPotential();
		}
	}

	void ColideManager2d::calculatePotential() {
		for (int i = 0; i < layers.size(); i++) {
			layers[i].calculatePotential();
		}
	}

	void ColideManager2d::updateObjects() {
		for (int i = 0; i < layers.size(); i++) {
			layers[i].update();
		}
	}

	void ColideManager2d::update() {
		checkPotential();
		updateObjects();
		calculatePotential();
	}
} }