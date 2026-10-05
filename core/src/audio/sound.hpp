#pragma once
#include "../utils/wav_file_reader.hpp"

namespace heartCore { namespace audio {
	class Sound {
	private:
		WavFile m_file;
		std::vector<uint8> m_buffer;
		uint16 m_channels;
		uint32 m_sampleRate;
		uint16 m_bitsPerSample;
		uint16 audioFormat;

	public:
		Sound(const char* filepath);
		~Sound();

		const std::vector<uint8> getBuffer() { return m_buffer; }

		const uint16& getChannels() { return m_channels; }
		const uint32& sampleRate() { return m_sampleRate;  }
		const uint16& bitsPerSample() { return m_bitsPerSample; }
		const uint16& audioFormat() { return audioFormat; }
		
	};
} }