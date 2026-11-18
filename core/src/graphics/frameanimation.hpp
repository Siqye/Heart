#pragma once
#include "../utils/cxxtimer.hpp"
#include "staticsprite.hpp"

namespace heartCore { namespace graphics {
	class Animation {
	private:
		Timer m_deltaTime;
		bool m_isPlaying;
		bool m_looping;

		int m_frameCount;
		int m_currentFrame;

		unsigned long long m_duration;

		//float m_uvOffsetX;
		//float m_uvOffsetY;

		//std::vector<maths::vec2> m_coords;
		Texture* m_currentFrameTexture;
		std::vector<Texture*> m_frames;

	public:
		Animation(std::vector<Texture*> frames, unsigned long long duration, bool looping);
		// бля потом решить как это сделать по человечесик
		//Animation(Texture* texture, std::vector<maths::vec2> frameStarts, float offsetX, float offsetY, float duration, bool looping = false);

		void play();
		void pause();

		void countinue();
		void reset();
		void nextSprite();
		
		inline const bool& isPlaying() { return m_isPlaying; }
		inline const bool& isLooping() { return m_looping; }
		inline Texture* getCurrentTexture() { return m_currentFrameTexture; }
		inline const unsigned long long getDurationTime() { return m_duration; }
	};
} }