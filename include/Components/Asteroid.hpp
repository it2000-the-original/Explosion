
std::vector<std::string> debrisAssets = {

    "meteor1",
    "meteor2"
};

class Asteroid : public Component {

private:

    int number;

    const float impulse = 0.05f;

    bool exp = false;

    b2BodyDef debrisDef;
    b2FixtureDef debrisFix;

public:

    Asteroid(int _number) {

        number = _number;

        setDefaultDebrisDefinition();
        setDefaultDebrisFixture();
    }

    void update() {

        if (exp) explode();
    }

    void onCollision2D(Entity* _entity) {

        if (_entity->getComponent<Body>().getCategory() == Claser) {

            exp = true;
            _entity->destroy();
        }
    }

    void explode() {

        entity->destroy();

        for (int i = 0; i < number; i++) {

            launchDebris(Engine::elements[debrisAssets[rand() % debrisAssets.size()]]);
        }
    }

    void launchDebris(Element* element) {

        debrisFix.shape = &element->shape;
        float direction = (rand() % 361) * 180.f / M_PI;

        auto& debris = entity->manager.addEntity();
        debris.addComponent<Body>(debrisDef, debrisFix);
        debris.addComponent<Sprite>(element);
        debris.addComponent<Destroyer>(2.f);
        debris.getComponent<Body>().body->SetTransform(entity->getComponent<Body>().body->GetPosition(), 0);
        debris.getComponent<Body>().applyImpulse(impulse, direction);
        Engine::manager.addToGrop(&debris, Gdebris);
    }

    void setDefaultDebrisDefinition() {

        debrisDef.type = b2_dynamicBody;
        debrisDef.bullet = true;
        debrisDef.linearDamping = 0.f;
        debrisDef.angularDamping = 0.f;
    }

    void setDefaultDebrisFixture() {

        debrisFix.density = 1.f;
        debrisFix.filter.categoryBits = Cdebris;
        debrisFix.filter.maskBits = Cdebris;
    }
};