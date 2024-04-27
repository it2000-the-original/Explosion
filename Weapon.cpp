#include "Engine.hpp"
#include "Components.hpp"

Weapon::Weapon(std::string name) 

	:element(Engine::elements[name]) {};

void Weapon::init() {

	body = &entity->getComponent<Body>();
}

void Weapon::update() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) shoot();

	else fired = false;
}

void Weapon::shoot() {

	if (!fired) {

		auto pos = body->getPosition();
		auto ang = body->getRotation();

		auto& body = loadLaser().getComponent<Body>();

		body.setRotation(ang);
		body.setPosition(pos);
		body.setVelocity(velocity, ang);

		fired = true;
	}
}

Entity& Weapon::loadLaser() {
	
	auto& laser = Engine::manager.addEntity();
	
	laser.addComponent<Body>      (getBodyDef(), getFixtureDef());
	laser.addComponent<Sprite>    (element);
	laser.addComponent<Teleporter>(false);
	laser.addComponent<Destroyer> (0.35f);

	Engine::manager.addToGrop(&laser, Glasers);

	return laser;
}

b2FixtureDef Weapon::getFixtureDef() {

	b2FixtureDef def;

	def.shape = &element->shape;
	def.friction    = 0.f;
	def.restitution = 0.f;
	def.density     = 0.001f;
	def.filter.categoryBits = Claser;
	def.filter.maskBits     = Casteroid;

	return def;
}

b2BodyDef Weapon::getBodyDef() {

	b2BodyDef def;

	def.type   = b2_dynamicBody;
	def.bullet = true;
	def.linearDamping  = 0.f;
	def.angularDamping = 0.f;
	def.fixedRotation  = true;

	return def;
}