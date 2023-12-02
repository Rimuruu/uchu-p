#include "uchu.h"
#include "entity/bullet.h"


Buffer::Buffer(unsigned int width, unsigned int heigth) {
	this->sizeX = width;
	this->sizeY = heigth;


}

Buffer::~Buffer() {
	
}



void init(Game* game) {

	


	game->is.game_input = &(game->input);
	game->p = new Player(100, 100, 100, 100, 10);
	game->p->isActive = 1;
	game->is.pushEntity(game->p);

}

void end(Game* game) {
	delete game->p;

}



void bouncingCube(Game* game) {
	static int srcX = 0;
	static int srcY = 0;
	static int destX = 100;
	static int destY = 100;
	static int vX = 1;
	static int vY = 1;
	const int speed = 10;
	
	


	drawRectangle(srcX, srcY, destX, destY, 0x12386f);

	srcX = srcX + (vX * speed);
	srcY = srcY + (vY * speed);
	destX = destX + (vX * speed);
	destY = destY + (vY * speed);

	if (srcX <= 0 || destX >= game->buffer.sizeX) {
		vX = -vX;
	}
	if (srcY <= 0 || destY >= game->buffer.sizeY) {
		vY = -vY;
	}

}

Bullet b(10, 10, 10, 10, 1, 0, 1);
void updateAndRender(Game* game) {


	b.update();
	game->is.update();
	game->p->update();
	
	drawRectangle(0, 0, game->buffer.sizeX, game->buffer.sizeY, 0);
	b.render();
	game->p->render();
	
	bouncingCube(game);





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

