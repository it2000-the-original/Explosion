#include <SFML/System.hpp>
#include <iostream>
#include <cmath>

struct Controller {

    const float rotationDamping = 0.025;
    const float linearForce = 0.25f;
    const float torque = 0.05f;

    void checkInputs(b2Body* body) {

        std::cout << body->GetPosition().x << std::endl;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveForward(body);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotateRight(body); else slowsRightRotation(body);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) rotateLeft(body);  else slowsLeftRotation(body);
    }

    void moveForward(b2Body* body) {

        float angle = body->GetAngle();

        b2Vec2 force = b2Vec2(
            linearForce * sin(angle),
            linearForce * -cos(angle)
        );

        body->ApplyForceToCenter(force, true);
    }

    void rotateRight(b2Body* body) {

        body->ApplyTorque(torque, true);
    }

    void rotateLeft(b2Body* body) {

        body->ApplyTorque(-torque, true);
    }

    void slowsRightRotation(b2Body* body) {

        if (body->GetAngularVelocity() > 0) {

            float angolarVelocity = body->GetAngularVelocity();
            float oppositeTorque = -angolarVelocity * rotationDamping;

            body->ApplyTorque(oppositeTorque, true);
        }
    }

    void slowsLeftRotation(b2Body* body) {

        if (body->GetAngularVelocity() < 0) {

            float angolarVelocity = body->GetAngularVelocity();
            float oppositeTorque = -angolarVelocity * rotationDamping;

            body->ApplyTorque(oppositeTorque, true);
        }
    }
};