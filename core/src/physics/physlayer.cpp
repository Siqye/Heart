#include "physlayer.hpp"

namespace heartCore { namespace physics {
	PhysLayer::PhysLayer() 
		: m_gravityAcceleration(0.0f), m_gravityDirection(maths::vec2())
	{}
	PhysLayer::~PhysLayer() {}

	void PhysLayer::checkPotential() {
		m_potential.clear();
		for (size_t i = 0; i < m_objects.size(); ++i) {
		for (size_t j = i + 1; j < m_objects.size(); ++j) {

			if (m_objects[i] && m_objects[j] && m_objects[i]->checkPotential(*m_objects[j])) {
				m_potential.push_back(m_objects[i]);
				m_potential.push_back(m_objects[j]);
			}

		}	}

		for (size_t i = 0; i < m_potential.size(); ++i) {
		for (size_t j = i + 1; j < m_potential.size(); ++j) {

			if (m_potential[i] && m_potential[j] && !m_potential[i]->checkPotential(*m_potential[j])) {

				m_potential.erase(std::remove(m_potential.begin(), m_potential.end(), m_potential[i]), m_potential.end());
				m_potential.erase(std::remove(m_potential.begin(), m_potential.end(), m_potential[j]), m_potential.end());
			}

		} }
	}

	void PhysLayer::calculatePotential() {
		for (size_t i = 0; i < m_potential.size(); ++i) {
		for (size_t j = i + 1; j < m_potential.size(); ++j) {

			if (m_potential[i] && m_potential[j])
				m_potential[i]->calculateAABB(*m_potential[j]);
		
		} }
	}

	void PhysLayer::update() {
		for (const auto& object : m_objects)
			if (object) object->update();
	}

	void PhysLayer::addObject(std::shared_ptr<ColideBox2d> object) {
		if (object) m_objects.push_back(std::move(object));
	}
} }