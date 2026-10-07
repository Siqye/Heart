#pragma once
#include "../config.h"
#include "soundfile.hpp"
#include <al.h>

namespace heartCore { namespace audio {
	class Sound {
	private:
		SoundData* m_soundData;
		// openal stuff
		ALenum m_format;
		ALuint m_buffer;
		ALuint m_source;

	public:
		Sound(SoundData* data);
		~Sound();

		void Play(bool looping, float x = 0, float y = 0, float z = 0);
		void Stop();
		const ALenum& getFormat() { return m_format; }
		
	};
} }