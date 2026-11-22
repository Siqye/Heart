#pragma once
#include "animation.hpp"

namespace heartCore { namespace graphics {
	class AtlasAnimation : public Animation {
	private:
		std::vector<std::vector<maths::vec2>> m_framesTC;
		int m_currentFrameIndex;
		int m_frameCount;
			bool m_finished;

		std::shared_ptr<Texture> m_texture;

		int m_offsetX;
		int m_offsetY;

		int m_pixelWidth;
		int m_pixelHeight;
	public:
		AtlasAnimation(std::vector<maths::vec2> framesStart, std::shared_ptr<Texture> atlas, int offsetX, int offsetY, unsigned long long duration_ms, bool looping = false);

		void play() override;
		void pause() override;

		void reset() override;
		void nextSprite(std::shared_ptr<StaticSprite> sprite) override;
			void update(std::shared_ptr<StaticSprite> sprite) override;
			bool isFinished() const override { return m_finished; }
	};
} }