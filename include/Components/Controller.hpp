#include <SFML/System.hpp>
#include <iostream>
#include <cmath>

class Controller : public Component {

private:

    Body* body;

public:

    const float rdamping = 0.05;

    const float boost = 0.5f;
    const float torsion = 0.1f;

    void init() {

        body = &entity->getComponent<Body>();
    }

    void update() {

        checkInputs();
    }

    void checkInputs() {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveForward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotateRight(); else slowsRightRotation();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) rotateLeft();  else slowsLeftRotation();
    }

    void moveForward() {

        float angle = body->body->GetAngle();

        b2Vec2 force = b2Vec2(
            boost * sin(angle),
            boost * -cos(angle)
        );

        body->body->ApplyForceToCenter(force, true);
    }

    void rotateRight() {

        body->body->ApplyTorque(torsion, true);
    }

    void rotateLeft() {

        body->body->ApplyTorque(-torsion, true);
    }

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