#include "read_mash_data.hpp"

namespace heartCore {

	float parseFloat(std::string string) {
		int exponentCoef = 1;
		int exponent = 0;
		float result = 0;

		for (int i = 0; i < string.size();i++) {
			if ( string[i] > 47 && string[i] < 58 ) {
				result += (float)(string[i] - 48) * (10^exponent);
				exponent += exponentCoef;
			} else if ( string[i] == 46 ) {
				exponentCoef = -1;
			}
		}

		return result;
	}

	std::vector<std::string> getPotentialNumbers(std::string line) {
		return { "huesos" };
	}

	MashData3d loadMashFile(const char* filepathOBJ) {
		std::string filedata = readFile(filepathOBJ);
		MashData3d resultMash;

		for (int i = 0; i < filedata.size();i++) {

		}

		return resultMash;

	}
}