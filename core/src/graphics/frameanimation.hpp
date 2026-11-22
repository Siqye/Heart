#pragma once
#include "../utils/cxxtimer.hpp"
#include "staticsprite.hpp"
#include "animation.hpp"
#include <memory>

namespace heartCore {
	namespace graphics {
		class FrameAnimation : public Animation {
		private:
			bool m_isPlaying;
			bool m_looping;

			int m_frameCount;
			int m_currentFrame;

			std::shared_ptr<Texture> m_currentFrameTexture;
			std::vector<std::shared_ptr<Texture>> m_frames;

		public:
			FrameAnimation(std::vector<std::shared_ptr<Texture>> frames, unsigned long long duration, bool looping = false);

			void play() override;
			void pause() override;

			void reset() override;
			void nextSprite(std::shared_ptr<StaticSprite> sprite) override;

			inline const bool& isPlaying() { return m_isPlaying; }
			inline const bool& isLooping() { return m_looping; }
		};
	}
}