#include "ecs/ecs.h"
#include "component/velocity.h"
#include "component/position.h"

struct Bullet : public Entity {
	int m[4];
	Bullet(int x, int y, int w, int h, int speed,int Vx,int Vy);



	void update();


	




};