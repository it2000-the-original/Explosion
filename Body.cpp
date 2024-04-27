#include "Engine.hpp"
#include "Components.hpp"

Body::Body(b2BodyDef def) {

    body = Engine::world->CreateBody(&def);
}

Body::Body(b2BodyDef def, b2FixtureDef fix) {

    body = Engine::world->CreateBody(&def);
    setFixture(fix);
} 

void Body::init() {

    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(entity);

}

void Body::setFixture(b2FixtureDef fix) {

    body->CreateFixture(&fix);
    category = fix.filter.categoryBits;
}

void Body::setRotation(float angle) {

    b2Vec2 pos = body->GetPosition();

    body->SetTransform(pos, angle);
}

void Body::setPosition(b2Vec2 pos) {

    body->SetTransform(pos, body->GetAngle());
}

void Body::setVelocity(float velocity, float angle) {

    // Imposta la velocità un modulo ed un angolo

    b2Vec2 vel = b2Vec2(
        velocity * sin(angle),
        velocity * -cos(angle)
    );

    body->SetLinearVelocity(vel);
}

void Body::applyForce(float force, float angle) {

    // Applica una forza con mudulo ed angolo

    b2Vec2 _force = b2Vec2(
        force * sin(angle), // Componente orizzontale
        force * -cos(angle) // Componente verticale
    );

    body->ApplyForceToCenter(_force, true);
}

void Body::applyImpulse(float impulse, float angle) {

    // Applica un impulso con modulo ed angolo

    b2Vec2 imp = b2Vec2(
        impulse * sin(angle), // Componente orizzontale
        impulse * -cos(angle) // Componente verticale
    );

    body->ApplyLinearImpulseToCenter(imp, true);
}

void Body::applyTorque(float torque) {

    body->ApplyTorque(torque, true);
}

void Body::applyAngularImpulse(float impulse) {

    body->ApplyAngularImpulse(impulse, true);
}

b2Vec2 Body::getPosition() {

    return body->GetPosition();
}

float Body::getRotation() {

    return body->GetAngle();
}

float Body::getVelocity() {

    b2Vec2 vel = body->GetLinearVelocity();
    return sqrt(pow(vel.x, 2) + pow(vel.y, 2));
}

float Body::getRVelocity() {

    return body->GetAngularVelocity();
}

int16 Body::getCategory() {

    return category;
}

Body::~Body() {

    Engine::world->DestroyBody(body);
}