#include "ecs/ecs.h"
#include "component/velocity.h"
#include "component/position.h"
#include "component/lifetime.h"
#include <memory>
#ifndef BULLET_H
#define BULLET_H
struct Bullet : public Entity {
	int lifetime = 5;
	Bullet(int x, int y, int w, int h, int speed,int Vx,int Vy);
	~Bullet();


	void update();
	void end();


	




};

void spawnBullet(int x, int y,int Vx,int Vy);



#endif // !1

