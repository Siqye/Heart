#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../config.h"

namespace heartCore {
    inline bool readU16(std::ifstream& file, uint16& value) {
        uint8 bytes[2];
        if (!file.read(reinterpret_cast<int8*>(bytes), sizeof(bytes)))
            return false;
        value = (uint16)bytes[0] |
                (uint16)bytes[1] << 8;
        return true;
    }

    inline bool readU32(std::ifstream& file, uint32& value) {
        uint8 bytes[4];
        if (!file.read(reinterpret_cast<int8*>(bytes), sizeof(bytes)))
            return false;
        value = (uint32)bytes[0] |
                (uint32)bytes[1] << 8 |
                (uint32)bytes[2] << 16 |
                (uint32)bytes[3] << 24;
        return true;
    }

    inline bool readTag(std::ifstream& file, const char* expected) {
        char tag[4];
        return file.read(tag, sizeof(tag)) &&
               tag[0] == expected[0] && tag[1] == expected[1] &&
               tag[2] == expected[2] && tag[3] == expected[3];
    }
}