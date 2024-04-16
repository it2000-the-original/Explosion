#include <SFML/System.hpp>
#include <iostream>
#include <cmath>

class Controller : public Component {

private:

    Body* body;

public:

    const float boost = 0.1f;      // Forza applicata per il movimento in avanti
    const float torsion = 0.025f;  // Forza di rotazione applicata dai comandi
    const float rdamping = 0.0125; // Questa attrito viene applicata solo quando non vi sono comandi di rotazione

    void init() {

        body = &entity->getComponent<Body>();
    }

    void update() {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveForward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotateRight(); else slowsRightRotation();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) rotateLeft();  else slowsLeftRotation();
    }

    void moveForward() {

        float angle = body->body->GetAngle();
        body->applyForce(boost, angle);
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
};