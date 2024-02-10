#pragma once
#include "ecs/ecs.h"
#include "position.h"



#ifndef BOX_H
#define BOX_H


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
#endif // !BOX_H
