#include "Engine.hpp"
#include "Random.hpp"
#include "Components.hpp"
#include "ExplosionsLoader.hpp"

#include "MonoBehaviour/Asteroid.hpp"

void Asteroid::init() {

	body = &entity->getComponent<Body>();
}

void Asteroid::update() {

	if (exp) explode();
}

void Asteroid::onCollision2D(Entity* e) {

	switch(e->getComponent<Body>().getCategory()) {

	case Claser: exp = true;

		e->destroy(); break;

	case Cplayer: exp = true;
	}
}

void Asteroid::explode() {

	entity->destroy();

	const explosion::Debris debris = {

		{ "debris1", "debris2" },
		{ "debris3", "debris4" },
		{ "debris5", "debris6" }
	};

	ExplosionDef expDef {"explosion", 48, 0.02f, debris, 3};

	ExplosionsLoader::loadExplosion(expDef, body->getPosition());
}