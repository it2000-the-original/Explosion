#include "Engine.hpp"
#include "Components.hpp"

#include "MonoBehaviour/Spaceship.hpp"

void Spaceship::init() {

	body = &entity->getComponent<Body>();

	loadFlame();
}

void Spaceship::update() {

	flame->getComponent<Sprite>().hide(true);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveForward();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotateRight(); else slowsRightRotation();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) rotateLeft();  else slowsLeftRotation();

	setFlamePosition();
}

void Spaceship::moveForward() {

	float angle = body->getRotation();

	body->applyForce(boost, angle);

	flame->getComponent<Sprite>().hide(false);
}

void Spaceship::rotateRight() {

	if (body->getRVelocity() < 15.f)
		body->applyTorque(torsion);
}

void Spaceship::rotateLeft() {

	if (body->getRVelocity() > -15.f)
		body->applyTorque(-torsion);
}

void Spaceship::slowsRightRotation() {

	if (body->getRVelocity() > 0) {

		float angolarVelocity = body->getRVelocity();
		float oppositeTorque = -angolarVelocity * rdamping;

		body->applyTorque(oppositeTorque);
	}
}

void Spaceship::slowsLeftRotation() {

	if (body->getRVelocity() < 0) {

		float angolarVelocity = body->getRVelocity();
		float oppositeTorque = -angolarVelocity * rdamping;

		body->applyTorque(oppositeTorque);
	}
}

b2BodyDef Spaceship::getFlameBodyDefinition() {

	b2BodyDef definition;

	definition.type = b2_dynamicBody;

	return definition;
}

b2FixtureDef Spaceship::getFlameFixtureDefinition() {

	b2FixtureDef definition;

	definition.density = 1.f;
	definition.shape = &Engine::elements["flame"]->shape;
	definition.filter.maskBits = 0x0000;

	return definition;
}

void Spaceship::loadFlame() {

	auto bodyDef = getFlameBodyDefinition();
	auto fixDef  = getFlameFixtureDefinition();

	flame = &Engine::manager.addEntity();
	flame->addComponent<Body>(bodyDef, fixDef);
	flame->addComponent<Sprite>(Engine::elements["flame"]);
	flame->addComponent<Animation>();

	Engine::manager.addToGrop(flame, Glasers);

	setFlameAnimations();
}

void Spaceship::setFlameAnimations() {

	auto& animation = flame->getComponent<Animation>();

	animation.addAnimation("base", 0, 2, 0.1f);
	animation.playAnimation("base");
}

void Spaceship::setFlamePosition() {

	b2Vec2 pos = body->getPosition();

	pos.x -= fDinstance * sin(body->getRotation());
	pos.y += fDinstance * cos(body->getRotation());

	auto& flameBody = flame->getComponent<Body>();

	flameBody.setPosition(pos);
	flameBody.setRotation(body->getRotation() + M_PI);
}