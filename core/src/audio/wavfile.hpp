#include "soundfile.hpp"

namespace heartCore { namespace audio {
	class WAVData : public SoundData {
	public:
		WAVData(const char* filepath);
		~WAVData();
	};
} }