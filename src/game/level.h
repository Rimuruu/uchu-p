#include "ecs/ecs.h"
#include "uchu.h"
#ifndef LEVEL_H
#define LEVEL_H
struct Tilemap {
	int width, height;
	int tileSize;
	unsigned int** map = nullptr;
	int x=0, y = 0;
	Tilemap(int x,int y,int width, int height,int tileSize,unsigned int** map);
	Tilemap() :width(0), height(0), tileSize(0), map(nullptr) {};
	~Tilemap();
};


struct Level : System {
	Tilemap* tilemap;

	void init();
	Level(Tilemap* t);
	void render();

};

void loadTilemap(Tilemap* t, int** map, int width, int height); 
void loadLevel(Game* game,Level* level);
void unloadLevel(Game* game);
#endif // !LEVEL_H
