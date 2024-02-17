#include "sprite.h"
#include "component/position.h"

SpriteComponent::SpriteComponent(Entity* e, ASSET_SPRITE sprite) {
	this->e = e;
	this->sprite = sprite;
}
void SpriteComponent::render() {
	Position2D* p = this->e->getComponent<Position2D>();
	if (p != nullptr) {
		drawImage(p->x, p->y, this->sprite);
	}
}