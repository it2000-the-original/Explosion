
class Weapon : public Component {

private:

    Body* body;

    b2BodyDef definition; // Definizione del corpo di un laser
    b2FixtureDef fixture; // Definizione di una fixture di un laser
    b2PolygonShape shape; // Forma del laser
    Element* element;     // Elemento di riferimento

    float velocity = 10.f;
    bool shot;

public:

    Weapon(Element* _element) {

        element = _element;
        _setDefaultDefinition();
        _setDefaultShape();
        _setDefaultFixture();
    }

    void init() {

        body = &entity->getComponent<Body>();
    }

    void update() {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

            if (!shot) { // Nel caso si tenesse premuta la spacebar

                shoot();
                shot = true;
            }
        }

        else shot = false;
    }

    void shoot() {

        b2Vec2 pos = body->body->GetPosition();
        float angle = body->body->GetAngle();

        auto& laser = entity->manager.addEntity();
        laser.addComponent<Body>(definition, fixture);
        laser.addComponent<Sprite>(element);
        laser.addComponent<Teleporter>();
        laser.addComponent<Destroyer>(0.35f);
        laser.getComponent<Body>().body->SetTransform(pos, angle);
        laser.getComponent<Body>().setVelocity(velocity, angle);
        Engine::manager.addToGrop(&laser, Gdebris);
    }

    void _setDefaultDefinition() {

        definition.type = b2_dynamicBody;
        definition.bullet = true;
        definition.linearDamping = 0.f;
        definition.angularDamping = 0.f;
        definition.fixedRotation = true;
    }

    void _setDefaultShape() {

        shape.SetAsBox(
            element->width * element->scale / WS / 2.f,
            element->height * element->scale / WS / 2.f
        );
    }

    void _setDefaultFixture() {

        fixture.shape = &shape;
        fixture.friction = 0.f;
        fixture.restitution = 0.f;
        fixture.density = 0.001f;
        fixture.filter.categoryBits = Claser;
        fixture.filter.maskBits = Casteroid;
    }
};