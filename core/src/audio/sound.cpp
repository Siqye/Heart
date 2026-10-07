#include "sound.hpp"

namespace heartCore { namespace audio { 
    ALenum setFormat(const uint16& channels, const uint16& bitsPerSample) {
        if (channels == 1 && bitsPerSample == 8)
            return AL_FORMAT_MONO8;
        else if (channels == 1 && bitsPerSample == 16)
            return AL_FORMAT_MONO16;
        else if (channels == 2 && bitsPerSample == 8)
            return AL_FORMAT_STEREO8;
        else if (channels == 2 && bitsPerSample == 16)
            return AL_FORMAT_STEREO16;
    }

	Sound::Sound(SoundData* data)
        : m_soundData(data)
    {
        const uint16& channels = data->getChannels();
        const uint16& bitsPerSample = data->getbitsPerSample();

        m_format = setFormat(channels, bitsPerSample);
        //m_buffer = 0;
        //m_source = 0;


        return;
	}

	Sound::~Sound() {
        alDeleteBuffers(1, &m_buffer);
        alDeleteSources(1, &m_source);
	}

    void Sound::Play(bool looping, float x, float y, float z) {
        const uint16& channels = m_soundData->getChannels();
        const uint16& bitsPerSample = m_soundData->getbitsPerSample();
        const std::vector<uint8>& data = m_soundData->getBuffer();
        const uint32 sampleRate = m_soundData->getSampleRate();

        alGenBuffers(1, &m_buffer);
        alBufferData(m_buffer, 
                     m_format, 
                     data.data(), 
                     (ALsizei)data.size(),
                     (ALsizei)sampleRate);

        alGenSources(1, &m_source);
        alSourcef(m_source, AL_PITCH, 1.0f);
        alSourcef(m_source, AL_GAIN, 1.0f);
        alSource3f(m_source, AL_POSITION, x, y, z);
        alSource3f(m_source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
        // AL_LOOPING is false by default
        if (looping) alSourcei(m_source, AL_LOOPING, AL_TRUE);
        alSourcei(m_source, AL_BUFFER, (ALint)m_buffer);

        alSourcePlay(m_source);
    }
    void Sound::Stop() {
        alDeleteBuffers(1, &m_buffer);
        alDeleteSources(1, &m_source);
    }

} }