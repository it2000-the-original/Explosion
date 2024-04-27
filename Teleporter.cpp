#include "Engine.hpp"
#include "Components.hpp"

Teleporter::Teleporter(bool _mirror) :mirror(_mirror) {}

void Teleporter::init() {

	body = &entity->getComponent<Body>();
	sprite = &entity->getComponent<Sprite>();
}

void Teleporter::update() {

	teleport();
	setXMirror();
	setYMirror();
}

void Teleporter::draw() {

	if (mirror) {

		if (xTeleporting) Engine::window->draw(xMirror);
		if (yTeleporting) Engine::window->draw(yMirror);
	}
}

void Teleporter::teleport() { // Sposta l'oggetto dall'altra estremità della finestra

	b2Vec2 pos = body->getPosition();

	if      (pos.x > WW / WS) pos.x = 0.f;
	else if (pos.x <   0.f  ) pos.x = WW / WS;
	if      (pos.y > WH / WS) pos.y = 0.f;
	else if (pos.y <   0.f  ) pos.y = WH / WS;

	body->setPosition(pos);
}

void Teleporter::setXMirror() {

	auto pos   = sprite->sprite.getPosition();
	auto hProj = getHorizontalProjection();
	xMirror    = sprite->sprite;

	setXTeleporting(hProj, &pos);

	xMirror.setPosition(pos);
}

void Teleporter::setYMirror() {

	auto pos   = sprite->sprite.getPosition();
	auto vProj = getVerticalProjection();
	yMirror    = sprite->sprite;

	setYTeleporting(vProj, &pos);

	yMirror.setPosition(pos);
}

void Teleporter::setXTeleporting(float proj, sf::Vector2f* pos) {

	if (rightMirror(proj, pos) or leftMirror(proj, pos)) {

		xTeleporting = true;
	}

	else xTeleporting = false;
}

void Teleporter::setYTeleporting(float proj, sf::Vector2f* pos) {

	if (upMirror(proj, pos) or downMirror(proj, pos)) {

		yTeleporting = true;
	}

	else yTeleporting = false;
}

float Teleporter::getHorizontalProjection() {

	float side1 = fabs(sprite->getWidth()  * cos(body->getRotation()));
	float side2 = fabs(sprite->getHeight() * sin(body->getRotation()));
	return (side1 + side2) / 2.f;
}

float Teleporter::getVerticalProjection() {

	float side1 = fabs(sprite->getWidth()  * sin(body->getRotation()));
	float side2 = fabs(sprite->getHeight() * cos(body->getRotation()));
	return (side1 + side2) / 2.f;
}

bool Teleporter::rightMirror(float proj, sf::Vector2f* pos) {

	if (pos->x + proj >= WW) {
		pos->x = pos->x - WW;
		return true;
	}

	return false;
}

bool Teleporter::leftMirror(float proj, sf::Vector2f* pos) {

	if (pos->x - proj < 0.f) {
		pos->x = pos->x + WW;
		return true;
	}

	return false;
}

bool Teleporter::downMirror(float proj, sf::Vector2f* pos) {

	if (pos->y + proj >= WH) {
		pos->y = pos->y - WH;
		return true;
	}

	return false;
}

bool Teleporter::upMirror(float proj, sf::Vector2f* pos) {

	if (pos->y - proj < 0.f) {
		pos->y = pos->y + WH;
		return true;
	}

	return false;
}