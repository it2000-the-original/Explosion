#include "Engine.hpp"
#include "Listener.hpp"
#include "Components.hpp"

void Listener::BeginContact(b2Contact* contact) {

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
	Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);

	if (entityA->hasComponent<MonoBehaviour>())
		entityA->getComponent<MonoBehaviour>().onCollision2D(entityB);

	if (entityB->hasComponent<MonoBehaviour>())
		entityB->getComponent<MonoBehaviour>().onCollision2D(entityA);
}