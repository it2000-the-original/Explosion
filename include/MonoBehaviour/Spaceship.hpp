#include <SFML/System.hpp>
#include <iostream>
#include <cmath>

class Spaceship : public MonoBehaviour {

private:

    Body* body;

    Entity* flame;

    const float boost = 0.3f;      // Forza applicata per il movimento in avanti
    const float torsion = 0.025f;  // Forza di rotazione applicata dai comandi
    const float rdamping = 0.0125; // Questa attrito viene applicata solo quando non vi sono comandi di rotazione
    const float fDinstance = 0.32f; // Distanza che la fiamma deve avere dal retro della navicella

    void moveForward() {

        float angle = body->body->GetAngle();
        body->applyForce(boost, angle);

        flame->getComponent<Sprite>().hide(false);
    }

    void rotateRight() {

        if (body->body->GetAngularVelocity() < 15.f)
            body->body->ApplyTorque(torsion, true);
    }

    void rotateLeft() {

        if (body->body->GetAngularVelocity() > -15.f)
            body->body->ApplyTorque(-torsion, true);
    }

    // Questa funzione, insieme alla successiva, servono a
    // rallentare il moto di rotazione quando non si sta premendo
    // alcun tasto per proseguirlo, applicando l'attrito specificato
    // all'inizio della classe

    void slowsRightRotation() {

        if (body->body->GetAngularVelocity() > 0) {

            float angolarVelocity = body->body->GetAngularVelocity();
            float oppositeTorque = -angolarVelocity * rdamping;

            body->body->ApplyTorque(oppositeTorque, true);
        }
    }

    void slowsLeftRotation() {

        if (body->body->GetAngularVelocity() < 0) {

            float angolarVelocity = body->body->GetAngularVelocity();
            float oppositeTorque = -angolarVelocity * rdamping;

            body->body->ApplyTorque(oppositeTorque, true);
        }
    }

    b2BodyDef getFlameBodyDefinition() {

        b2BodyDef definition;

        definition.type = b2_dynamicBody;

        return definition;
    }

    b2FixtureDef getFlameFixtureDefinition() {

        b2FixtureDef definition;

        definition.density = 1.f;
        definition.shape = &Engine::elements["flame"]->shape;
        definition.filter.maskBits = 0x0000;

        return definition;
    }

    void loadFlame() {

        b2BodyDef bodyDef = getFlameBodyDefinition();
        b2FixtureDef fixDef = getFlameFixtureDefinition();

        flame = &Engine::manager.addEntity();
        flame->addComponent<Body>(bodyDef, fixDef);
        flame->addComponent<Sprite>(Engine::elements["flame"]);
        flame->addComponent<Animation>();
        Engine::manager.addToGrop(flame, Glasers);

        setFlameAnimations();
    }

    void setFlameAnimations() {

        auto& animation = flame->getComponent<Animation>();

        animation.addAnimation("base", 0, 2, 100);
        animation.playAnimation("base");
    }

    void setFlamePosition() {

        b2Vec2 pos = body->getPosition();

        pos.x -= fDinstance * sin(body->body->GetAngle());
        pos.y += fDinstance * cos(body->body->GetAngle());

        auto& flameBody = flame->getComponent<Body>();

        flameBody.setPosition(pos);
        flameBody.setRotation(body->body->GetAngle() + M_PI);
    }

public:

    void init() {

        body = &entity->getComponent<Body>();

        loadFlame();
    }

    void update() {

        flame->getComponent<Sprite>().hide(true);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveForward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotateRight(); else slowsRightRotation();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) rotateLeft();  else slowsLeftRotation();

        setFlamePosition();
    }
};