#pragma once
#include "ecs/ecs.h"
#include "position.h"





struct Box : public Component {
	int w, h;
	Box() = default;
	Box(Entity* e, int w, int h) {
		this->w = w;
		this->h = h;
		this->e = e;
	}
	
	void render();




};