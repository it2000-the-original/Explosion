#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

/* This is the header file that define all of the classes to manage for the
 * Entity Component System, in fact there is a Component class that acts as a polymorphism
 * to create other components, an entity class that define his components and a manager class
 * to manage all of the entities in the system. */

class Component;
class Entity;
class Manager;

const int MC = 32; // Max Components

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
};

class Entity {

private:

	bool active = true;
	Component* CArray[MC];

public:

	Manager& manager;
	std::vector<Component*> components;

	Entity(Manager& mManager) : manager(mManager) {}

	void update() {

		for (auto& c : components) c->update();
	}

	void draw() {

		for (auto& c : components) c->draw();
	}

	bool isActive() { 
	
		return active;
	}

	void destroy() {
	
		active = false;
	}

	template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {

		T* c = new T(std::forward<TArgs>(mArgs)...);

		c->entity = this;
		components.emplace_back(std::move(c));
		CArray[getComponentID<T>()] = c;
		c->init();
		return *c;
	}

	template <typename T> T& getComponent() const {

		auto ptr = CArray[getComponentID<T>()];
		return *static_cast<T*>(ptr);
	}

	~Entity() {

		for (int i = int(components.size()) - 1; i >= 0; i--) {

			delete components[i];
			components.erase(components.begin() + i);
		}
	}
};

class Manager {

private:

	std::vector<Entity*> entities;

public:

	void update() {

		for (int i = 0; i < entities.size(); i++) entities[i]->update();
	}

	void draw() {

		for (auto& e : entities) e->draw();
	}

	void refersh() {

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](Entity* mEntity) {

			if (!mEntity->isActive()) {
				delete mEntity;
				return true;
			}

			else return false;

		}), std::end(entities));
	}

	Entity& addEntity() {

		Entity* e = new Entity(*this);
		entities.emplace_back(std::move(e));
		return *e;
	}
};