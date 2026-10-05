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

	void Speaker::playSound(Sound* sound) {
		ALenum format = 0;

		const uint16& channels = sound->getChannels();
		const uint16& bitsPerSample = sound->getbitsPerSample();
		const uint32& sampleRate = sound->getSampleRate();

		const std::vector<uint8> soundBuffer = sound->getBuffer();

		if (channels == 1 && bitsPerSample == 8)
			format = AL_FORMAT_MONO8;
		else if (channels == 1 && bitsPerSample == 16)
			format = AL_FORMAT_MONO16;
		else if (channels == 2 && bitsPerSample == 8)
			format = AL_FORMAT_STEREO8;
		else if (channels == 2 && bitsPerSample == 16)
			format = AL_FORMAT_STEREO16;

		ALuint buffer = 0;
		ALuint source = 0;
		alGenBuffers(1, &buffer);
		alBufferData(buffer, format, soundBuffer.data(), (ALsizei)soundBuffer.size(),
			(ALsizei)sampleRate);
		alGenSources(1, &source);
		alSourcef(source, AL_PITCH, 1.0f);
		alSourcef(source, AL_GAIN, 1.0f);
		alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
		alSourcei(source, AL_LOOPING, AL_FALSE);
		alSourcei(source, AL_BUFFER, (ALint)buffer);

		alSourcePlay(source);

		ALint state = AL_PLAYING;
		alGetSourcei(source, AL_SOURCE_STATE, &state);
		if (state == AL_PLAYING) {
			
		}
		
		
	}

} }