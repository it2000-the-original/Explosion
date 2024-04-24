// Questo componente gestisce un corpo della libreria Box2D

class Body : public Component {

private:

    int16 category; // il tipo di oggetto

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

    void setRotation(float angle) {

        b2Vec2 pos = body->GetPosition();

        body->SetTransform(pos, angle);
    }

    void setPosition(b2Vec2 pos) {

        body->SetTransform(pos, body->GetAngle());
    }

    void setVelocity(float velocity, float angle) {

        // Imposta la velocità un modulo ed un angolo

        b2Vec2 vel = b2Vec2(
            velocity * sin(angle),
            velocity * -cos(angle)
        );

        body->SetLinearVelocity(vel);
    }

    void applyForce(float force, float angle) {

        // Applica una forza con mudulo ed angolo

        b2Vec2 _force = b2Vec2(
            force * sin(angle), // Componente orizzontale
            force * -cos(angle) // Componente verticale
        );

        body->ApplyForceToCenter(_force, true);
    }

    void applyImpulse(float impulse, float angle) {

        // Applica un impulso con modulo ed angolo

        b2Vec2 imp = b2Vec2(
            impulse * sin(angle), // Componente orizzontale
            impulse * -cos(angle) // Componente verticale
        );

        body->ApplyLinearImpulseToCenter(imp, true);
    }

    void applyAngularImpulse(float impulse) {

        body->ApplyAngularImpulse(impulse, true);
    }

    b2Vec2 getPosition() {

        return body->GetPosition();
    }

    float getVelocity() {

        b2Vec2 vel = body->GetLinearVelocity();
        return sqrt(pow(vel.x, 2) + pow(vel.y, 2));
    }

    int16 getCategory() {

        return category;
    }

    ~Body() {

        Engine::world->DestroyBody(body);
    }
};