#include "ecs/ecs.h"
#include "component/velocity.h"
#include "component/position.h"
#include <memory>
#ifndef BULLET_H
#define BULLET_H
struct Bullet : public Entity {
	int m[4];
	Bullet(int x, int y, int w, int h, int speed,int Vx,int Vy);
	~Bullet();


	void update();


	




};

void spawnBullet(int x, int y,int Vx,int Vy);



#endif // !1

