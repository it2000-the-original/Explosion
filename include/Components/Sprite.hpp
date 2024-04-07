#include <SFML/Graphics.hpp>

struct Sprite {

    sf::Sprite sprite;

    Sprite(Element* element) {

        sprite.setTexture(element->texture);
        sprite.setScale(sf::Vector2f(element->scale, element->scale));
        sprite.setOrigin(sf::Vector2f(element->width / 2.f, element->height / 2.f));
    }

    void update(b2Body* body) {

        b2Vec2 pos = body->GetPosition();
        float ang = body->GetAngle();

        sprite.setPosition(sf::Vector2f(pos.x * WS, pos.y * WS));
        sprite.setRotation(ang * 180.f / M_PI);
    }

    void draw(sf::RenderWindow* window) {

        window->draw(sprite);
    }
};