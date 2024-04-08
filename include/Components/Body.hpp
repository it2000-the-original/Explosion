// Questo componente gestisce un corpo della libreria Box2D

class Body : public Component {

public:

    b2Body* body;

    Body(b2BodyDef definition) {

        body = Engine::world->CreateBody(&definition);
    }

    Body(b2BodyDef definition, b2FixtureDef fixture) {

        body = Engine::world->CreateBody(&definition);
        setFixture(fixture);
    } 

    void setFixture(b2FixtureDef fixture) {

        body->CreateFixture(&fixture);
    }
};