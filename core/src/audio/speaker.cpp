#include "speaker.hpp"
#include <stdio.h>
#include <iostream>

namespace heartCore { namespace audio {
	Speaker::Speaker() {
		m_device = alcOpenDevice(nullptr);
		if (!m_device) {
			std::cout << "Failed to open default OpenAL device\n";
			return;
		}

		m_context = alcCreateContext(m_device, nullptr);
		if (!m_context) {
			std::cerr << "Failed to create OpenAL context\n";
			alcCloseDevice(m_device);
			return;
		}

		alcMakeContextCurrent(m_context);
	}

	Speaker::~Speaker() {
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
	}
} }