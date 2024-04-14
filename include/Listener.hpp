
class Listener : public b2ContactListener {

    void BeginContact(b2Contact* contact) {

        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();

        Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
        Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);

        entityA->onCollision2D(entityB);
        entityB->onCollision2D(entityA);
    }
};