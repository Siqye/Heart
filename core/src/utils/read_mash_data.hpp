#include "file_reader.hpp"
#include "../maths/maths.hpp"
#include <vector>


namespace heartCore {
	struct MashData3d {
		std::vector<maths::vec3> vertecies;
		std::vector<int> indecies;
	};

	MashData3d loadMashFile(const char* filepathOBJ);
}