#include "ecs.h"







void System::init() {

}
void System::update() {

}
void System::render() {

}
void System::end() {

}




void Entity::init() {

}

void Entity::handleInput(u_int32 keyCode, short state) {

}

void Entity::update() {
	for (Component* c : components) {
		if (c  && c->isActive) {
			c->update();
		}
	}
}
void Entity::render() {
	for (Component* c : components) {
		if (c  && c->isActive) {
			c->render();
	
			
		}
	}

}
void Entity::end() {
	for (Component* c : components) {
		if (c) {
			c->end();
			delete c;
		}
	}
}

void Component::init() {

}
void Component::update() {

}
void Component::render() {

}
void Component::end() {

}

