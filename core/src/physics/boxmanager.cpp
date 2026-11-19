#include "boxmanager.hpp"

namespace heartCore { namespace physics {
	ColideManager2d::ColideManager2d() {
	}

	ColideManager2d::~ColideManager2d() { }

	void ColideManager2d::checkPotential() {
		for (const auto& layer : layers) {
			if (layer) layer->checkPotential();
		}
	}

	void ColideManager2d::calculatePotential() {
		for (const auto& layer : layers) {
			if (layer) layer->calculatePotential();
		}
	}

	void ColideManager2d::updateObjects() {
		for (const auto& layer : layers) {
			if (layer) layer->update();
		}
	}

	void ColideManager2d::update() {
		checkPotential();
		updateObjects();
		calculatePotential();
	}


	void ColideManager2d::addLayer(std::shared_ptr<PhysLayer> layer) {
		if (layer) layers.push_back(std::move(layer));
	}

	void ColideManager2d::addBox(std::shared_ptr<ColideBox2d> object, int layerID) {
		if (!object || layerID < 0 || static_cast<size_t>(layerID) >= layers.size() || !layers[layerID])
			return;
		layers[layerID]->addObject(std::move(object));
	}

} }