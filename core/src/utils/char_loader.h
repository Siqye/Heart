#pragma once
#include <freetype-gl.h>

namespace heartCore {
	inline void loadChar(texture_atlas_t* atlas) {
        if (!atlas->id)
        {
            glGenTextures(1, &atlas->id);
        }

        glBindTexture(GL_TEXTURE_2D, atlas->id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

#       if 1
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, atlas->width, atlas->height,
            0, GL_BGR, GL_UNSIGNED_BYTE, atlas->data);
#       else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlas->width, atlas->height,
            0, GL_RED, GL_UNSIGNED_BYTE, atlas->data);
#       endif
	}
}