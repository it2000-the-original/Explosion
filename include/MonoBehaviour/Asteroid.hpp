// Questa classe contiene l'algoritmo vero e proprio

using Level = std::vector<std::string>;

const Level level1_assets {

    "debris1", "debris2"
};

const Level level2_assets {

    "debris3", "debris4",
};

const Level level3_assets {

    "debris5", "debris6",
};

class Asteroid : public MonoBehaviour {

private:

    int number; // Numero dei rottami da scagliare

    const float minImpulse = 0.01; // Impulso da applicare (su base 1000)
    const float maxImpulse = 0.05; // Possibile variazione dell'impulso (su base 1000)

    const float minAImpulse = -0.001;
    const float maxAImpulse = +0.001;

    bool exp = false; // Se true, l'asteroide esploderà

    b2BodyDef debrisDef;
    b2FixtureDef debrisFix;

    std::vector<Level> levels {

        level1_assets,
        level2_assets,
        level3_assets
    };

public:

    Asteroid(int _number) :number(_number) {

        setDefaultDebrisDefinition();
        setDefaultDebrisFixture();
    }

    void update() {

        if (exp) explode();
    }

    void onCollision2D(Entity* _entity) {

        if (_entity->getComponent<Body>().getCategory() == Claser) {

            _entity->destroy();
            exp = true;
        }
    }

    void explode() {

        entity->destroy();

        for (int i = 0; i < levels.size(); i++)
        for (int j = 0; j < pow(number, i + 1); j++) {

            std::string asset = levels[i][ex::random(int(levels[i].size() - 1))];
            launchDebris(Engine::elements[asset]);
        }
    }

    void launchDebris(Element* element) {

        debrisFix.shape = &element->shape;
        float direction = ex::random(360);
        float impulse   = ex::random(minImpulse,  maxImpulse);  // Impulso direzionale
        float aImpulse  = ex::random(maxAImpulse, minAImpulse); // Impulso angolare (rotazione)

        auto& dBody = loadDebris(element).getComponent<Body>(); // Debris body
        auto& aBody = entity->getComponent<Body>();             // Asteroid body

        dBody.setPosition(aBody.getPosition());
        dBody.applyImpulse(impulse, direction);
        dBody.applyAngularImpulse(aImpulse);

    }

    Entity& loadDebris(Element* element) {

        auto& debris = Engine::manager.addEntity();

        debris.addComponent<Body>(debrisDef, debrisFix);
        debris.addComponent<Sprite>(element);
        debris.addComponent<Destroyer>(2.f);

        Engine::manager.addToGrop(&debris, Gdebris);

        return debris;
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
        debrisFix.filter.maskBits = 0x0000;
    }
};