#pragma once
#include <vector>
#include <array>
#include "logger.h"

#define MAX_COMPONENT 1024

typedef unsigned int u_int32;

struct System;
struct Entity;
struct Component;
struct Button_state;

int componentId();

template <typename T> int getComponentTypeID() {
	static int id = componentId();
	return id;
}

struct System {
	std::vector<Entity*> entities = { nullptr };


	template <typename T, typename... Targs>
	T& addEntity(Targs&&... mArgs) {
		T* e = new T(mArgs...);
		entities.emplace(e);
	}


	void pushEntity(Entity* e) {

		this->entities.emplace_back(e);
	}

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void end();
};
struct Entity {
	int isActive;
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


	virtual void init();
	virtual void update();
	virtual void handleInput(u_int32 keyCode, short state);
	virtual void render();
	virtual void end();
};
struct Component {
	Entity* e;
	int isActive;
	int id;
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void end();
};
