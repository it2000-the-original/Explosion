#include "Engine.hpp"
#include "Random.hpp"
#include "Components.hpp"

#include "MonoBehaviour/Asteroid.hpp"

const Level level1_assets {

    "debris1", "debris2"
};

const Level level2_assets {

    "debris3", "debris4",
};

const Level level3_assets {

    "debris5", "debris6",
};

Asteroid::Asteroid() {

	setBodyDef();
	setFixtureDef();
	setLevels();
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

	for (int i = 0; i < levels.size();      i++)
	for (int j = 0; j < pow(number, i + 1); j++) {

		int assetID = ex::random(int(levels[i].size() - 1));
		std::string asset = levels[i][assetID];

		launchDebris(Engine::elements[asset]);
	}
}

void Asteroid::launchDebris(Element* element) {

	float direction = ex::random(360);
	float impulse   = ex::random(minImpulse,  maxImpulse);  // Impulso direzionale
	float aImpulse  = ex::random(maxAImpulse, minAImpulse); // Impulso angolare (rotazione)

	auto& dBody = loadDebris(element).getComponent<Body>(); // Debris body
	auto& aBody = entity->getComponent<Body>();             // Asteroid body

	dBody.setPosition(aBody.getPosition());
	dBody.applyImpulse(impulse, direction);
	dBody.applyAngularImpulse(aImpulse);
}

Entity& Asteroid::loadDebris(Element* element) {

	fixtureDef.shape = &element->shape;

	auto& debris = Engine::manager.addEntity();

	debris.addComponent<Body>     (bodyDef, fixtureDef);
	debris.addComponent<Sprite>   (element);
	debris.addComponent<Destroyer>(2.f);

	Engine::manager.addToGrop(&debris, Gdebris);

	return debris;
}

void Asteroid::setBodyDef() {

	bodyDef.bullet = true;
	bodyDef.type   = b2_dynamicBody;
	bodyDef.linearDamping  = 0.f;
	bodyDef.angularDamping = 0.f;
}

void Asteroid::setFixtureDef() {

	fixtureDef.density = 1.f;
	fixtureDef.filter.categoryBits = Cdebris;
	fixtureDef.filter.maskBits     = 0x0000;
}

void Asteroid::setLevels() {

	levels = {

		level1_assets,
		level2_assets,
		level3_assets
	};
}