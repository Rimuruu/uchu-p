#include "ecs/ecs.h"
#include "graphic.h"
#include "asset.h"
#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

struct SpriteComponent : Component {
	ASSET_SPRITE sprite;
	SpriteComponent(Entity* e, ASSET_SPRITE sprite);
	void render();
};


#endif