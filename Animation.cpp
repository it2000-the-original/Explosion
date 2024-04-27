#include "Engine.hpp"
#include "Components.hpp"

void Animation::addAnimation(std::string name, int i, int f, int s) {

	ani::AnimationData ani(i, f, s);
	animations.emplace(name, ani);
}

void Animation::playAnimation(std::string name) {

	index = animations[name].index;
	frames = animations[name].frames;
	speed = sf::milliseconds(animations[name].speed);

	animating = true;
	clock.restart();
}

void Animation::init() {

	sprite = &entity->getComponent<Sprite>();
}

void Animation::update() {

	if (animating and clock.getElapsedTime() >= speed) {

    	frame = (frame + 1) % frames;

		sf::IntRect rect( // Indica la posizione nel frame all'interno dell'immagine
			sprite->getWidth()  / sprite->getScale() * frame,
            sprite->getHeight() / sprite->getScale() * index,
            sprite->getWidth()  / sprite->getScale(),
            sprite->getHeight() / sprite->getScale()
        );

        sprite->sprite.setTextureRect(rect);

        clock.restart();
    }
}