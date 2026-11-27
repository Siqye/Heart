#pragma once
#include <string>
#include <vector>

namespace heartCore {
	std::string readFile(const char* file_path);
	std::vector<char> readFileBinary(const char* file_path);
}