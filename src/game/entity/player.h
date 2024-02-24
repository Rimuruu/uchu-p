#include "ecs/ecs.h"
#include "component/velocity.h"
#include "component/position.h"
#include "key_binding.h"
#include "sound.h"
#include "component/input.h"
#include "component/sprite.h"
#include "system/system.h"
#ifndef PLAYER_H
#define PLAYER_H

struct Player : public Entity {
	int m[4] = {0};
	Player(int x, int y, int w, int h, int speed);
	void end();



	

};

std::shared_ptr<Entity> spawnPlayer(int x, int y);


#endif // !PLAYER_H


