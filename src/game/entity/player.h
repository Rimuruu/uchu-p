#pragma once
#include "ecs/ecs.h"
#include "component/velocity.h"
#include "component/position.h"
#include "key_binding.h"

struct Player : public Entity {
	int m[4] = {0};
	Player(int x, int y, int w, int h, int speed);


	void update();

	void move();

	void handleInput(u_int32 keyCode, short state);

	void setMove(int dir, int state);


};