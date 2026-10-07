#include "sound.hpp"

namespace heartCore { namespace audio {

    bool readU16(std::ifstream& file, uint16& value) {
        uint8 bytes[2];
        if (!file.read(reinterpret_cast<int8*>(bytes), sizeof(bytes)))
            return false;
        value = (uint16)bytes[0] |
            (uint16)bytes[1] << 8;
        return true;
    }

    bool readU32(std::ifstream& file, uint32& value) {
        uint8 bytes[4];
        if (!file.read(reinterpret_cast<int8*>(bytes), sizeof(bytes)))
            return false;
        value = (uint32)bytes[0] |
            (uint32)bytes[1] << 8 |
            (uint32)bytes[2] << 16 |
            (uint32)bytes[3] << 24;
        return true;
    }

    bool readTag(std::ifstream& file, const char* expected) {
        char tag[4];
        return file.read(tag, sizeof(tag)) &&
            tag[0] == expected[0] && tag[1] == expected[1] &&
            tag[2] == expected[2] && tag[3] == expected[3];
    }
    
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

	Sound::Sound(const char* filepath) {
        std::ifstream file(filepath, std::ios::binary);
        if (!file)
            return;

        uint32 riffSize = 0;
        if (!readTag(file, "RIFF") || !readU32(file, riffSize) ||
            !readTag(file, "WAVE")) {
            std::cerr << "ERROR: invalid WAV RIFF header\n";
            return;
        }

        bool hasFormat = false;
        bool hasData = false;
        uint32 chunkSize = 0;

        while (file && (!hasFormat || !hasData)) {
            char chunkId[4];
            if (!file.read(chunkId, sizeof(chunkId)) || !readU32(file, chunkSize))
                break;

            const bool isFormat = chunkId[0] == 'f' && chunkId[1] == 'm' &&
                chunkId[2] == 't' && chunkId[3] == ' ';
            const bool isData = chunkId[0] == 'd' && chunkId[1] == 'a' &&
                chunkId[2] == 't' && chunkId[3] == 'a';

            if (isFormat) {
                if (chunkSize < 16 || !readU16(file, m_audioFormat) ||
                    !readU16(file, m_channels) || !readU32(file, m_sampleRate))
                    return;

                uint32 byteRate = 0;
                uint16 blockAlign = 0;
                if (!readU32(file, byteRate) || !readU16(file, blockAlign) ||
                    !readU16(file, m_bitsPerSample))
                    return;

                const std::streamoff remaining = static_cast<std::streamoff>(chunkSize) - 16;
                if (remaining > 0)
                    file.seekg(remaining, std::ios::cur);
                hasFormat = true;
            }
            else if (isData) {
                m_dataBuffer.resize(chunkSize);
                if (!file.read(reinterpret_cast<char*>(m_dataBuffer.data()), chunkSize))
                    return;
                hasData = true;
            }
            else {
                file.seekg(chunkSize, std::ios::cur);
            }

            if (chunkSize & 1)
                file.seekg(1, std::ios::cur);
        }

        if (!hasFormat || !hasData || m_audioFormat != 1 ||
            (m_channels != 1 && m_channels != 2) ||
            (m_bitsPerSample != 8 && m_bitsPerSample != 16) ||
            m_dataBuffer.empty()) {
            std::cerr << "ERROR: only mono/stereo PCM WAV (8 or 16 bit) is supported\n";
            return;
        }
        m_format = setFormat(m_channels, m_bitsPerSample);
        
        m_buffer = 0;
        m_source = 0;

        alGenBuffers(1, &m_buffer);
        alGenSources(1, &m_source);

        return;
	}

	Sound::~Sound() {

	}

    void Sound::Play(bool looping, float x, float y, float z) {
        alBufferData(m_buffer, m_format, m_dataBuffer.data(), (ALsizei)m_dataBuffer.size(),
            (ALsizei)m_sampleRate);
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