#include "Engine.hpp"
#include "Random.hpp"
#include "Components.hpp"
#include "ExplosionsLoader.hpp"

using namespace explosion;

const float ExplosionsLoader::minImpulse  = 0.01;
const float ExplosionsLoader::maxImpulse  = 0.05;
const float ExplosionsLoader::minAImpulse = -0.001;
const float ExplosionsLoader::maxAImpulse = +0.001;

b2BodyDef    ExplosionsLoader::dBDef; // Definitione del corpo dei detriti
b2BodyDef    ExplosionsLoader::eBDef; // Definizione del corpo dell'esplosione
b2FixtureDef ExplosionsLoader::dFDef; // Fixture dei detriti
b2FixtureDef ExplosionsLoader::eFDef; // Fixture dell'esplosione

void ExplosionsLoader::loadExplosion(ExplosionDef def, b2Vec2 pos) {

	for (int i = 0; i < def.debris.size();              i++)
	for (int j = 0; j < pow(def.debrisQuantity, i + 1); j++) {

		int ID = ex::random(int(def.debris[i].size() - 1));

		std::string asset = def.debris[i][ID];

		_launchDebris(asset, pos);
	}

	_launchExplosion(def, pos);
}

void ExplosionsLoader::init() {

	_setDebrisDef();
	_setExplosionDef();
}

void ExplosionsLoader::_setDebrisDef() {

	dBDef.type = b2_dynamicBody;
	dBDef.bullet = true;
	dBDef.linearDamping = 0.f;
	dBDef.angularDamping = 0.f;

	dFDef.density = 1.f;
	dFDef.filter.categoryBits = Cdebris;
	dFDef.filter.maskBits = Cnone;
}

void ExplosionsLoader::_setExplosionDef() {

	eBDef.type = b2_kinematicBody;
	eBDef.linearDamping = 0.f;
	eBDef.angularDamping = 0.f;

	eFDef.density = 1.f;
	eFDef.filter.categoryBits = Cnone; 
	eFDef.filter.maskBits = Cnone;
}

Entity& ExplosionsLoader::_loadDebris(std::string e) {

	dFDef.shape = &Engine::elements[e]->shape;

	auto& debris = Engine::manager.addEntity();

	debris.addComponent<Body>(dBDef, dFDef);
	debris.addComponent<Sprite>(Engine::elements[e]);
	debris.addComponent<Destroyer>(2.f);

	Engine::manager.addToGrop(&debris, Gdebris);

	return debris;
}

Entity& ExplosionsLoader::_loadExplosion(ExplosionDef def) {

	float time = def.frames * def.speed;

	eFDef.shape = &Engine::elements[def.element]->shape;

	auto& explosion = Engine::manager.addEntity();
	explosion.addComponent<Body>(eBDef, eFDef);
	explosion.addComponent<Sprite>(def.element);
	explosion.addComponent<Animation>();
	explosion.addComponent<Destroyer>(time, false);
	Engine::manager.addToGrop(&explosion, Glasers);

	return explosion;
}

void ExplosionsLoader::_launchDebris(std::string e, b2Vec2 pos) {

	auto& body = _loadDebris(e).getComponent<Body>();

	float direction = ex::random(360);
	float impulse   = ex::random(minImpulse,  maxImpulse);  // Impulso direzionale
	float aImpulse  = ex::random(maxAImpulse, minAImpulse); // Impulso angolare (rotazione)

	body.setPosition(pos);
	body.applyImpulse(impulse, direction);
	body.applyAngularImpulse(aImpulse);		
}

void ExplosionsLoader::_launchExplosion(ExplosionDef def, b2Vec2 pos) {

	auto& explosion = _loadExplosion(def);	

	explosion.getComponent<Body>().setPosition(pos);
	explosion.getComponent<Animation>().addAndPlay("exp", 0, def.frames, def.speed);
}