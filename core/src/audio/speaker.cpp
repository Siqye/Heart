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

	void Speaker::playSound(Sound* sound, bool looping, float x, float y, float z) {
		const uint16& channels = sound->getChannels();
		const uint16& bitsPerSample = sound->getbitsPerSample();
		const uint32& sampleRate = sound->getSampleRate();
		const std::vector<uint8> soundBuffer = sound->getBuffer();
		const ALenum format = sound->getFormat();

		m_buffer = 0;
		m_source = 0;
		alGenBuffers(1, &m_buffer);
		alBufferData(m_buffer, format, soundBuffer.data(), (ALsizei)soundBuffer.size(),
			(ALsizei)sampleRate);
		alGenSources(1, &m_source);
		alSourcef(m_source, AL_PITCH, 1.0f);
		alSourcef(m_source, AL_GAIN, 1.0f);
		alSource3f(m_source, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSource3f(m_source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
		// AL_LOOPING is false by default
		if (looping) alSourcei(m_source, AL_LOOPING, AL_TRUE);
		alSourcei(m_source, AL_BUFFER, (ALint)m_buffer);

		alSourcePlay(m_source);
	}
} }