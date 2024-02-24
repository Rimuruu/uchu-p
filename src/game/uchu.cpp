#include "uchu.h"
#include "asset.h"
Buffer::Buffer(unsigned int width, unsigned int heigth) {
	this->sizeX = width;
	this->sizeY = heigth;


}

Buffer::~Buffer() {
	
}

Game* global_game = nullptr;
BMPFile* defaultTexture;
void init(Game* game) {
	global_game = game;
	unsigned int ** map = new unsigned int*[4];
	static int x=0, y=0;
	for (size_t i = 0; i < 4; i++)
	{
		map[i] = new unsigned int[4];
		for (int y = 0; y < 4; y++)
			map[i][y] = TEST3;
	}

	loadImage("./assets/img/t2.bmp",TEST2);
	loadImage("./assets/img/t.bmp", TEST);
	loadImage("./assets/img/t3.bmp", TEST3);
	loadSound("./assets/sound/shoot.wav", SHOOT);
	is.game_input = &(game->input);
	Tilemap* t = new Tilemap(x,y,4, 4, 40,map);
	Level* l = new Level(t);
	loadLevel(game,l);

	for (size_t i = 0; i < 4; i++)
	{
		delete map[i];
	
	}
	delete map;
	x+=10;
	y+=10;

}

void end(Game* game) {
	delete game->l;

}

void nextLevel() {
	unloadLevel(global_game);
	init(global_game);
}





void updateAndRender(Game* game) {



	// update system do specific action on component

	// update all entities k

	is.update();
	ms.update();



	drawRectangle(0, 0, game->buffer.sizeX, game->buffer.sizeY, 0);
	game->l->render();
	gs.render();
	cl.update();
	game->l->tilemap->y += 10;




}

Node_button::Node_button(Button_state val) {
	this->val = val;
	this->next = nullptr;
}


Button_state Game_input::pop(){
	Node_button* curr = this->head;
	Button_state val = {0,0};
	if (this->head) {
		val = curr->val;
		this->head = curr->next;
		delete curr;
		this->front--;
	}
	return val;
}	


void Game_input::queue(Button_state key) {
	if (this->front >= this->size) return;
	Node_button* curr = this->head;
	if (!curr) {
		this->head = new Node_button(key);
		this->front++;
		return;
	}
	while (curr->next) {
		curr = curr->next;
	}
	curr->next = new Node_button(key);
	this->front++;
	
	
}

