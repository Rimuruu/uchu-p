#include "uchu.h"
#include "asset.h"
Buffer::Buffer(unsigned int width, unsigned int heigth) {
	this->sizeX = width;
	this->sizeY = heigth;


}

Buffer::~Buffer() {
	
}


BMPFile* defaultTexture;
void init(Game* game) {

	loadImage("./assets/img/t2.bmp",TEST2);
	loadImage("./assets/img/t.bmp", TEST);

	loadSound("./assets/sound/shoot.wav", SHOOT);

	ms.entities.size();
	is.game_input = &(game->input);
	game->p = new Player(100, 100, 100, 100, 10);
	game->p->isActive = 1;
	auto pp = is.pushEntity(game->p);
	ms.pushEntity(pp);
	gs.pushEntity(pp);

}

void end(Game* game) {
	delete game->p;

}







void updateAndRender(Game* game) {



	// update system do specific action on component

	// update all entities k

	is.update();
	ms.update();



	drawRectangle(0, 0, game->buffer.sizeX, game->buffer.sizeY, 0);
	gs.render();
	cl.update();




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

