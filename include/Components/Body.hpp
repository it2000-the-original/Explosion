#include <box2d/box2d.h>

struct Body {

    b2Body* body;

    Body(b2World* world, b2BodyType type) {

        b2BodyDef definition;
        definition.type = type;

        body = world->CreateBody(&definition);
    }

    Body(b2World* world, b2BodyType type, float x, float y) {

        b2BodyDef definition;
        definition.type = type;
        definition.position.Set(x, y);

        body = world->CreateBody(&definition);
    }

    void setShape(b2PolygonShape shape, float density) {

        b2FixtureDef fixture;
        fixture.shape = &shape;
        fixture.density = density;

        body->CreateFixture(&fixture);
    }

    void setShape(b2CircleShape shape, float density) {

        b2FixtureDef fixture;
        fixture.shape = &shape;
        fixture.density = density;

        body->CreateFixture(&fixture);
    }
};