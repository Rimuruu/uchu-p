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


	void pushEntity(Entity * e) {
		std::shared_ptr < Entity> ePtr{e};

		this->entities.push_back(std::move(ePtr));


	}

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void end();
};
struct Entity {
	int isActive = true;
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
	int isActive=true;
	int id;
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void end();
};

#endif
