#pragma once
#include "../utils/cxxtimer.hpp"
#include "API/staticsprite.hpp"
#include "API/texture.hpp"
#include "animation.hpp"
#include <memory>

namespace heartCore {
	namespace graphics {
		using namespace API;
		class FrameAnimation : public Animation {
		private:
			int m_frameCount;
			int m_currentFrame;
			bool m_finished;

			std::shared_ptr<Texture> m_currentFrameTexture;
			std::vector<std::shared_ptr<Texture>> m_frames;

		public:
			FrameAnimation(std::vector<std::shared_ptr<Texture>> frames, unsigned long long duration, bool looping = false);

			void play() override;
			void pause() override;

			void reset() override;
			void nextSprite(std::shared_ptr<StaticSprite> sprite) override;
			void update(std::shared_ptr<StaticSprite> sprite) override;
			bool isFinished() const override { return m_finished; }

			inline const bool& isPlaying() { return m_isPlaying; }
			inline const bool& isLooping() { return m_looping; }
		};
	}
}