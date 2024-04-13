
class Listener : public b2ContactListener {

    void BeginContact(b2Contact* contact) {

        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();

        Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
        Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);

        for (auto& c : entityA->components) c->onCollision2D(entityB);
        for (auto& c : entityB->components) c->onCollision2D(entityA);
    }
};