#include "level.h"


Tilemap::Tilemap(int x,int y,int width, int height,int tileSize, unsigned int** map) {
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->x = x;
	this->y = y;
	if (map != nullptr) 
	{
		this->map = new unsigned int* [width];
		for (size_t x = 0; x < this->width; x++)
		{
			this->map[x] = new unsigned int [height];
			for (size_t y = 0; y < this->height ; y++)
			{
				this->map[x][y] = map[x][y];
			}

			
		}
		
	}
}

Tilemap::~Tilemap() {
	if (this->map != nullptr) {
		for (size_t x = 0; x < this->width; x++)
		{
			
			if (this->map[x] != nullptr) delete[] this->map[x];
			
		}
		delete[] this->map;
	}
}

void loadTilemap(Tilemap* t, int** map, int width, int height) {
// to todo

}

void Level::init() {
	auto pp = spawnPlayer(10,10);
	this->pushEntity(pp);
}

void Level::render() {
	for (size_t x = 0; x < this->tilemap->height; x++)
	{
		for (size_t y = 0; y < this->tilemap->width; y++)
		{
			drawImage(x*this->tilemap->tileSize + this->tilemap->x, y * this->tilemap->tileSize + this->tilemap->y, this->tilemap->map[x][y]);
		}
	}
}



Level::Level(Tilemap* t) {
	this->tilemap = t;
}


void loadLevel(Game* game, Level* level) {
	game->l = level;
	game->l->init();
}

void unloadLevel(Game* game) {

	for (std::shared_ptr<Entity>e : game->l->entities) {
		if (e) {
			e->isDestroyed = 2;
			game->l->removedEntity(e.get());
		}
	}
	
	game->l = nullptr;
	
}