#if defined(_MSC_VER)
#pragma disable(warning:4996)
#endif 

#include <string>
#include <al.h>
#include <alc.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

namespace heartCore {
    struct WAVHeader {
        char riff[4];        //RIFF
        uint32_t chunkSize;
        char wave[4];        //WAVE
        char fmt[4];         //fmt
        uint32_t subchunk1Size;
        uint16_t audioFormat; //PCM always 1
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;
        char dataHeader[4];  //data
        uint32_t dataSize;
    };


    inline bool 
    loadWAVFile(const std::string& filename, ALuint& buffer, ALuint& source, bool loop) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error: Cannot open file " << filename << "\n";
            return false;
        }

        WAVHeader header{};
        file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

        if (std::string(header.riff, 4) != "RIFF" || std::string(header.wave, 4) != "WAVE") {
            std::cerr << "Error: Invalid WAV file format.\n";
            return false;
        }
        if (header.audioFormat != 1) { // PCM only
            std::cerr << "Error: Unsupported WAV format (only PCM supported).\n";
            return false;
        }

        std::vector<char> data(header.dataSize);
        file.read(data.data(), header.dataSize);

        ALenum format;
        if (header.numChannels == 1) {
            format = (header.bitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
        }
        else if (header.numChannels == 2) {
            format = (header.bitsPerSample == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
        }
        else {
            std::cerr << "Error: Unsupported channel count.\n";
            return false;
        }

        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, data.data(), static_cast<ALsizei>(data.size()), header.sampleRate);

        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);

        return true;
    }
}