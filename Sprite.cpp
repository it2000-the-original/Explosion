#include "Engine.hpp"
#include "Components.hpp"

Sprite::Sprite(std::string name) {

	auto element = Engine::elements[name].get();

    scale =  element->scale;
    width =  element->width  * element->scale;
    height = element->height * element->scale;
        
    sprite.setTexture(element->texture);
    sprite.setScale(sf::Vector2f(scale, scale));
    sprite.setOrigin(sf::Vector2f(width / scale / 2.f, height / scale / 2.f));
    sprite.setTextureRect(sf::IntRect(0, 0, width / scale, height / scale));
}

void Sprite::init() {

    body = &entity->getComponent<Body>();

	b2Vec2 sz(width / WS, height / WS);

	body->setSize(sz);
}

void Sprite::update() {

    b2Vec2 pos = body->getPosition();
    float  ang = body->getRotation();

    pos.x *= WS;
    pos.y *= WS;

    ang = ang * 180.f / M_PI; // Converto le radianti in gradi

    sprite.setRotation(ang);
    sprite.setPosition(sf::Vector2f(pos.x, pos.y));
}

void Sprite::draw() {

    if (show) Engine::window->draw(sprite);
}

void Sprite::hide(bool val) {

    show = !val;
}

float Sprite::getWidth() {

    return width;
}

float Sprite::getHeight() {

    return height;
}

float Sprite::getScale() {

    return scale;
}