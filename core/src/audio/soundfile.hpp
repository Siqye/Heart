#pragma once
#include "../config.h"
#include "../utils/sound_data_reader.hpp"

namespace heartCore { namespace audio {
	class SoundData {
	protected:
		std::vector<uint8> m_dataBuffer;
		uint16 m_channels;
		uint32 m_sampleRate;
		uint16 m_bitsPerSample;
		uint16 m_audioFormat;

	public:
		SoundData() {}
		~SoundData() {}

		const std::vector<uint8> getBuffer() const { return m_dataBuffer; }

		const uint16& getChannels() const { return m_channels; }
		const uint32& getSampleRate() const { return m_sampleRate; }
		const uint16& getbitsPerSample() const { return m_bitsPerSample; }
		const uint16& getAudioFormat() const { return m_audioFormat; }
	};
} }