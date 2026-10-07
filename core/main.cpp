#include "src/utils/timer.hpp"
#include "src/graphics/window.hpp"
#include "src/graphics/sprite.hpp"
#include "src/graphics/texture.hpp"
#include "src/graphics/layers/group.hpp"
#include "src/graphics/layers/levellayer.hpp"
#include "src/graphics/layers/scenelayer.hpp"
#include "src/graphics/packetrenderer.hpp"
#include "src/graphics/label.hpp"
#include "src/graphics/fontmanager.hpp"
#include "src/audio/sound.hpp"
#include "src/audio/speaker.hpp"

using namespace heartCore;
using namespace graphics;
using namespace audio;

int main()
{
	Window window(800, 600, "Heart");

	Shader shader("src/shader/basic.vert", "src/shader/basic.frag");

	Texture* textures[] = {
		new Texture("test/test1.png"),
		new Texture("test/test2.png"),
		new Texture("test/test3.png"),
		new Texture("test/test4.png"),
		new Texture("test/test5.png")
	};

	int texIDs[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 };

	shader.bind();
	shader.setUniform1iv("textures", 32, texIDs);

	FontManager fm("test\\fonts");

	LevelLayer layer(&shader);
	//SceneLayer layer3d(&shader);

	for (float x = 0; x < 4; x += 0.3f) {
		for (float y = 0; y < 3; y += 0.3f) {
			layer.add(new Sprite(x, y, 0.25, 0.25, textures[rand() % 5]));
		}
	}
	Timer timer;
	int fps = 0;
	std::string labelFPS = "0 fps";

	Speaker speaker;

	Sound sound("sound.wav");

	maths::vec4 textColor = maths::vec4(1, 1, 1, 1);
	Label labelfps(labelFPS, 3, 0.3f, 2.3f, textColor, fm.getFontbyID(0));
	Label* lfps = &labelfps;

	layer.add(lfps);

	double x, y;
	//speaker.playSound(&sound);
	sound.Play(false);
	while (window.close()) {
		window.clear();

		window.getMousePosition(x, y);
		shader.bind();
		shader.setUniform2f("ligth_pos", maths::vec2(
			-x * 4.0f / 800.0f,
			-3.0f + y * 3.0f / 600.0f
		));

		layer.render();
		
		if (window.isKeyPressed(GLFW_KEY_S)) sound.Stop();

		labelfps = Label(labelFPS, 3, 0.3f, 2.3f, textColor, fm.getFontbyID(0));

		window.update();

		fps++;
		if (timer.elapsed() >= 1.0) {
			labelFPS = std::to_string(fps);
			labelFPS += " fps";
			timer.reset();
			fps = 0;
		}
	}
	return 0;
}