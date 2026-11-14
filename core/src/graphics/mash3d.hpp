#pragma once

#include "../maths/mat4.hpp"
#include <vector>

namespace heartCore { namespace graphics {
	class Mash3d {
	private:
		struct MashData {
			std::vector<maths::vec3> m_vertecies;
			std::vector<int> m_indecies;
		};

		MashData m_data;
		public:
		Mash3d(const char* OBJfilepath);

		virtual const std::vector<maths::vec3>& getVertecies() { return m_vertecies; }
		virtual const std::vector<int>& getIndecies() { return m_indecies; }
	};
} }