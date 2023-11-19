#include "ecs.h"



int componentId() {
	 static int id = -1;
	 id++;
	 return id;
}









void Entity::init() {

}
void Entity::update() {

}
void Entity::render() {
	for (Component* c : components) {
		if (c) {
			c->render();
		}
	}

}
void Entity::end() {

}

void Component::init() {

}
void Component::update() {

}
void Component::render() {

}
void Component::end() {

}