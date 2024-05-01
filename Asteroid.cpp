#include "Engine.hpp"
#include "Random.hpp"
#include "Components.hpp"
#include "ExplosionsLoader.hpp"

#include "MonoBehaviour/Asteroid.hpp"

const explosion::Debris debris = {

	{ "debris1", "debris2"},
	{ "debris3", "debris4"},
	{ "debris5", "debris6"}
};

ExplosionDef expDef {"explosion", 48, 0.02f, debris, 3};

void Asteroid::init() {

	body = &entity->getComponent<Body>();
}

void Asteroid::update() {

	if (exp) explode();
}

void Asteroid::onCollision2D(Entity* e) {

	if (e->getComponent<Body>().getCategory() == Claser) {

		e->destroy();
		exp = true;
	}
}

void Asteroid::explode() {

	entity->destroy();

	ExplosionsLoader::loadExplosion(expDef, body->getPosition());
}