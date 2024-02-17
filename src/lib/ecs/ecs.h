#pragma once
#include <vector>
#include <array>
#include "logger.h"
#include <memory>

#ifndef ECS_H
#define ECS_H


#define MAX_COMPONENT 1024

typedef unsigned int u_int32;

struct System;
struct Entity;
struct Component;
struct Button_state;

inline int componentId() {
	static int id = -1;
	id++;
	return id;
}


template <typename T> inline int getComponentTypeID() {
	static int id = componentId();
	return id;
}

struct System {
	std::vector<std::shared_ptr<Entity>> entities;


	template <typename T, typename... Targs>
	T& addEntity(Targs&&... mArgs) {

		entities.emplace(std::make_shared<Entity>(mArgs...));
	}


	std::shared_ptr < Entity> pushEntity(Entity * e) {
		std::shared_ptr < Entity> ePtr{e};

		this->entities.push_back(ePtr);
		return ePtr;


	}

	void pushEntity(std::shared_ptr < Entity> e) {
		

		this->entities.push_back(std::move(e));


	}

	void removedEntity(Entity* e) {
		std::vector<std::shared_ptr<Entity>>::iterator it;

		for (it = entities.begin(); it != entities.end(); it++) {
			Entity* itE = it->get();
			if (itE == e) {
				entities.erase(it);
				break;
			}
		}
				
	}

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void end();
};
struct Entity {
	int isActive = 1;
	int isDestroyed = 0;
	std::array<Component*, MAX_COMPONENT> components = { nullptr };
	template <typename T, typename... Targs>
	void addComponent(Targs&&... mArgs)
	{
		T* c = new T(this,mArgs...);
		c->id = getComponentTypeID<T>();
		this->components[c->id] = c;

	}


	template <typename T>
	T* getComponent() {
		int id = getComponentTypeID<T>();
		return (T*)components[id];
	}

	virtual ~Entity();
	virtual void init();
	virtual void update();
	virtual void handleInput(u_int32 keyCode, short state);
	virtual void render();
	virtual void end();
};
struct Component {
	Entity* e;
	int isActive=1;
	int id;
	virtual ~Component();
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void end();
};

#endif
