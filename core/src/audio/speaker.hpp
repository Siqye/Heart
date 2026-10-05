#pragma once
#include <al.h>
#include <alc.h>
#include "sound.hpp"

namespace heartCore { namespace audio {
	
	
	class Speaker {
	private:
		ALCdevice* m_device;
		ALCcontext* m_context;
		ALuint m_buffer;
		ALuint m_source;
	public:
		Speaker();
		~Speaker();

		void playSound(Sound* sound);
	};
} }