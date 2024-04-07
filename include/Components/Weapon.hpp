#include <SFML/System.hpp>

struct Weapon {

    float impulse = 0.03f;
    entt::registry* registry;
    b2Body* spaceship;
    Element* laser;

    Weapon(Element* _laser, b2Body* _spaceship, entt::registry* _registry) {

        laser = _laser;
        spaceship = _spaceship;
        registry = _registry;
    }

    void checkInputs() {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

            shoot();
        }
    }

    void shoot() {

        b2World* world = spaceship->GetWorld();
        auto entity = registry->create();

        auto body = registry->emplace<Body>(entity, world, b2_dynamicBody, 1.f, 1.f);
        registry->emplace<Sprite>(entity, laser);
        registry->emplace<Teleporter>(entity);

        b2PolygonShape shape;
        shape.SetAsBox(laser->width / WS / 2.f, laser->height / WS / 2.f);

        body.setShape(shape, 0.1f);
        body.body->SetTransform(body.body->GetPosition(), spaceship->GetAngle());

        applyImpulse(body.body);
    }

    void applyImpulse(b2Body* body) {

        float angle = body->GetAngle();

        b2Vec2 _impulse = b2Vec2(
            impulse * sin(angle),
            impulse * -cos(angle)
        );

        body->ApplyLinearImpulseToCenter(_impulse, true);
    }
};