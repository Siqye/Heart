#include "physlayer.hpp"

namespace heartCore { namespace physics {
	PhysLayer::PhysLayer() 
		: m_gravityAcceleration(0.0f), m_gravityDirection(maths::vec2())
	{}
	PhysLayer::~PhysLayer() {}

	void PhysLayer::checkPotential() {
		for (int i = 0; i < m_objects.size(); i++) {	
		for (int j = m_objects.size(); j > 0; j--) {

			if (m_objects[i] != m_objects[j] && m_objects[i]->checkPotential(m_objects[j])) {
				m_potential.push_back(m_objects[i]);
				m_potential.push_back(m_objects[j]);
			}

		}	}

		for (int i = 0; i < m_potential.size(); i++) {
		for (int j = m_potential.size(); j > 0; j--) {

			if (!m_potential[i]->checkPotential(m_potential[j])) {

				auto it = std::find(m_potential.begin(), m_potential.end(), m_potential[i]);
				if (it != m_potential.end())
					m_potential.erase(it);

				it = std::find(m_potential.begin(), m_potential.end(), m_potential[j]);
				if (it != m_potential.end())
					m_potential.erase(it);
			}

		} }
	}

	void PhysLayer::calculatePotential() {
		for (int i = 0; i < m_potential.size(); i++) {
		for (int j = m_potential.size(); j > 0; j++) {

			if (m_potential[i] != m_potential[j])
				m_potential[i]->calculateAABB(m_potential[j]);
		
		} }
	}

	void PhysLayer::update() {
		for (int i = 0; i < m_objects.size(); i++)
			m_objects[i]->update();
	}

	void PhysLayer::addObject(ColideBox2d* object) {
		m_objects.push_back(object);
	}
} }