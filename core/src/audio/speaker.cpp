#include "speaker.hpp"
#include "../logger/logger.hpp"

namespace heartCore { namespace audio {
	Speaker::Speaker() {
		m_device = alcOpenDevice(nullptr);
		if (!m_device) {
			LOG_ERROR("Failed to open default audio device");
			return;
		}

		m_context = alcCreateContext(m_device, nullptr);
		if (!m_context) {
			LOG_ERROR("Failed to create OpenAL context");
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