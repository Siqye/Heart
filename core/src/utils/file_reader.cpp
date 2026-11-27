#include "file_reader.hpp"
#include <fstream>

namespace heartCore {
	std::string readFile(const char* file_path)
	{
		FILE* file = nullptr;
		if (fopen_s(&file, file_path, "rt") != 0 || file == nullptr) {
			return std::string();
		}
		fseek(file, 0, SEEK_END);
		unsigned long file_size = ftell(file);
		char* data = new char[file_size + 1];
		memset(data, 0, file_size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, file_size, file);
		fclose(file);

		std::string result(data);
		delete[] data;

		return result;
	}

	std::vector<char> readFileBinary(const char* file_path)
	{
		std::ifstream file(file_path, std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			return {};
		}
		std::vector<char> data(static_cast<size_t>(file.tellg()));
		file.seekg(0);
		file.read(data.data(), static_cast<std::streamsize>(data.size()));
		return data;
	}
}