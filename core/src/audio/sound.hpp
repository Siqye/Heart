#pragma once
#include "../config.h"
#include <vector>
#include <fstream>
#include <cstdint>
#include <string>
#include <iostream>

namespace heartCore { namespace audio {
	class Sound {
	private:
		//WavFile m_file;
		std::vector<uint8> m_buffer;
		uint16 m_channels;
		uint32 m_sampleRate;
		uint16 m_bitsPerSample;
		uint16 m_audioFormat;

	public:
		Sound(const char* filepath);
		~Sound();

		const std::vector<uint8> getBuffer() { return m_buffer; }

		const uint16& getChannels() { return m_channels; }
		const uint32& getSampleRate() { return m_sampleRate;  }
		const uint16& getbitsPerSample() { return m_bitsPerSample; }
		const uint16& getAudioFormat() { return m_audioFormat; }
		
	};
} }