// Questo componente gestisce un corpo della libreria Box2D

class Body : public Component {

private:

    int16 category;

public:

    b2Body* body;

    Body(b2BodyDef definition) {

        body = Engine::world->CreateBody(&definition);
    }

    Body(b2BodyDef definition, b2FixtureDef fixture) {

        body = Engine::world->CreateBody(&definition);
        setFixture(fixture);
    } 

    void init() {

        body->GetUserData().pointer = reinterpret_cast<uintptr_t>(entity);
    }

    void setFixture(b2FixtureDef fixture) {

        body->CreateFixture(&fixture);
        category = fixture.filter.categoryBits;
    }

    void setVelocity(float velocity, float angle) {

        b2Vec2 vel = b2Vec2(
            velocity * sin(angle),
            velocity * -cos(angle)
        );

        body->SetLinearVelocity(vel);
    }

    void applyForce(float force, float angle) {

        b2Vec2 _force = b2Vec2(
            force * sin(angle),
            force * -cos(angle)
        );

        body->ApplyForceToCenter(_force, true);
    }

    void applyImpulse(float impulse, float angle) {

        b2Vec2 imp = b2Vec2(
            impulse * sin(angle),
            impulse * -cos(angle)
        );

        body->ApplyLinearImpulseToCenter(imp, true);
    }

    int16 getCategory() {

        return category;
    }

    ~Body() {

        Engine::world->DestroyBody(body);
    }
};