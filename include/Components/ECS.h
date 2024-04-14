#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <bitset>
#include <array>

/* This is the header file that define all of the classes to manage for the
 * Entity Component System, in fact there is a Component class that acts as a polymorphism
 * to create other components, an entity class that define his components and a manager class
 * to manage all of the entities in the system. */

class Component;
class Entity;
class Manager;

const int MC = 32; // Max Components
const int MG = 32; // Max Groups

using Components = std::vector<std::unique_ptr<Component>>;
using CBitset = std::bitset<MC>;
using CArray = std::array<Component*, MC>;
using GArray = std::array<std::vector<Entity*>, MG>;

using Entities = std::vector<std::unique_ptr<Entity>>;

inline int getNewComponentID() {

	static int newID = 0;
	return newID++;
}

template <typename T> inline int getComponentID() noexcept {

	static int ID = getNewComponentID();
	return ID;
}

class Component {

public:

	Entity* entity;         
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	virtual ~Component() {}

	virtual void onCollision2D(Entity* _entity) {}
};


class Entity {

private:

	Components components;
	CBitset cbitset;
	CArray carray;

	bool active = true;

public:

	Manager& manager;

	Entity(Manager& mManager) : manager(mManager) {}

	void update() {

		for (auto& c : components) c->update();
	}

	void draw() {

		for (auto& c : components) c->draw();
	}

	void onCollision2D(Entity* entity) {

		for (auto& c : components) c->onCollision2D(entity);
	}

	bool isActive() { 
	
		return active;
	}

	void destroy() {
	
		active = false;
	}

	template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {

		T* c = new T(std::forward<TArgs>(mArgs)...);
		std::unique_ptr<Component> uPtr(c);

		components.emplace_back(std::move(uPtr));
		cbitset.set(getComponentID<T>(), 1);
		carray[getComponentID<T>()] = c;

		c->entity = this;
		c->init();
		return *c;
	}

	template <typename T> bool hasComponent() const {

		return cbitset[getComponentID<T>()];
	}

	template <typename T> T& getComponent() const {

		auto ptr = carray[getComponentID<T>()];
		return *static_cast<T*>(ptr);
	}

	~Entity() {}
};

class Manager {

private:

	Entities entities;
	GArray groups;

public:

	void update() {

		for (int i = 0; i < entities.size(); i++) entities[i]->update();
	}

	void draw() {

		for (auto& e : entities) e->draw();
	}

	void refersh() {

		refershGroups();

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
		[](const std::unique_ptr<Entity> &entity) {
			
			return !entity->isActive();

		}), std::end(entities));
	}

	Entity& addEntity() {

		Entity* e = new Entity(*this);
		entities.emplace_back(std::move(e));
		return *e;
	}

	void addToGrop(Entity* entity, std::size_t group) {
		
		groups[group].emplace_back(std::move(entity));
	}

	std::vector<Entity*>& getGroup(std::size_t group) {

		return groups[group];
	}

	void refershGroups() {

		for (int i = 0; i < MG; i++) {

			groups[i].erase(std::remove_if(std::begin(groups[i]), std::end(groups[i]), 
			[i](Entity* entity) {
			
				return !entity->isActive();

			}), std::end(groups[i]));
		}
	}
};