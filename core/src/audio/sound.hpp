#pragma once
#include "../config.h"
#include <vector>
#include <fstream>
#include <cstdint>
#include <string>
#include <iostream>
#include <al.h>

namespace heartCore { namespace audio {
	class Sound {
	private:
		//WavFile m_file;
		std::vector<uint8> m_dataBuffer;
		uint16 m_channels;
		uint32 m_sampleRate;
		uint16 m_bitsPerSample;
		uint16 m_audioFormat;
		// openal stuff
		ALenum m_format;
		ALuint m_buffer;
		ALuint m_source;

	public:
		Sound(const char* filepath);
		~Sound();

		void Play(bool looping, float x = 0, float y = 0, float z = 0);
		void Stop();

		const std::vector<uint8> getBuffer() { return m_dataBuffer; }

		const uint16& getChannels() { return m_channels; }
		const uint32& getSampleRate() { return m_sampleRate;  }
		const uint16& getbitsPerSample() { return m_bitsPerSample; }
		const uint16& getAudioFormat() { return m_audioFormat; }
		const ALenum& getFormat() { return m_format; }
		
	};
} }