#include "ecs/ecs.h"
#include "uchu.h"
#include "entity/bullet.h"


#ifndef INPUT_H
#define INPUT_H
struct InputComponent : public Component {
	int m[4] = { 0 };
	void handle(Button_state b);
	void setMove(int dir, int state);
	InputComponent(Entity * e);
	void update();


};
#endif // !INPUT_H

