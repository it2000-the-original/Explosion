#include "Engine.hpp"
#include "Components.hpp"

Destroyer::Destroyer(float _time, bool _trans) 

	:time(sf::seconds(_time)), transition(_trans) {}

void Destroyer::init() {

	sprite = &entity->getComponent<Sprite>();

	clock.restart();
}

void Destroyer::update() {

	setTransparency();

	if (clock.getElapsedTime() >= time) {

		entity->destroy();
	}
}

void Destroyer::setTransparency() {

	// Con questa funzione la transparenza di uno sprite,
	// progredisce in base al tempo rimanente prima della
	// distruzione, usando una semplice proporzione

	auto color = sprite->sprite.getColor();

	sf::Time passedTime = clock.getElapsedTime();
	sf::Time remainTime = time - passedTime;

	color.a = 255 * remainTime.asSeconds() / time.asSeconds();

	sprite->sprite.setColor(color);
}