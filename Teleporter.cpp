#include "Engine.hpp"
#include "Components.hpp"

void Teleporter::init() {

	body = &entity->getComponent<Body>();
}

void Teleporter::update() {

	teleport();
}

void Teleporter::teleport() { // Sposta l'oggetto dall'altra estremità della finestra

	b2Vec2 pos = body->getPosition();
	auto hProj = getHorizontalProjection() / 2.f;
	auto vProj = getVerticalProjection()   / 2.f;

	if      (pos.x - hProj >= WW / WS) pos.x = -hProj;
	else if (pos.x + hProj < 0.f)      pos.x = WW / WS + hProj;
	if      (pos.y - vProj >= WH / WS) pos.y = -vProj;
	else if (pos.y + vProj < 0.f)      pos.y = WH / WS + vProj;

	body->setPosition(pos);
}

float Teleporter::getHorizontalProjection() {

	float side1 = fabs(body->getSize().x * cos(body->getRotation()));
	float side2 = fabs(body->getSize().y * sin(body->getRotation()));
	return side1 + side2;
}

float Teleporter::getVerticalProjection() {

	float side1 = fabs(body->getSize().x * sin(body->getRotation()));
	float side2 = fabs(body->getSize().y * cos(body->getRotation()));
	return side1 + side2;
}