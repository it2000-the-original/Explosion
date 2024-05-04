#include "Engine.hpp"
#include "Components.hpp"
#include "Background.hpp"

Background::Background(std::string b) {

	background = b;
	backDef.type = b2_kinematicBody;
}

void Background::drawBackground() {

	auto e = Engine::elements[background].get();

	int width =  e->width  * e->scale;
	int height = e->height * e->scale;
	int xrepeat = WW / width + 1;
	int yrepeat = WH / height + 1;

	for (int i = 0; i < yrepeat; i++) {

		drawLine(height / WS * (i + 0.5f), xrepeat, width);
	}
}

void Background::drawLine(float ypos, int xrepeat, int width) {

	for (int i = 0; i < xrepeat; i++) {

		b2Vec2 pos = b2Vec2(width / WS * (i + 0.5f), ypos);
		auto& panel = Engine::manager.addEntity();
		panel.addComponent<Body>(backDef);
		panel.addComponent<Sprite>(background);
		panel.getComponent<Body>().setPosition(pos);
		Engine::manager.addToGrop(&panel, Gbackground);
	}
}