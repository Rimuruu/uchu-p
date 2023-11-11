#include "uchu.h"




Buffer::Buffer(unsigned int width, unsigned int heigth) {
	this->sizeX = width;
	this->sizeY = heigth;


}

Buffer::~Buffer() {
	
}


struct player {
	int x = 0;
	int y = 0;
	int vX = 0;
	int vY = 0;
	int velocity = 10;
	void update() {
		this->x = this->x + (vX * velocity);
		this->y = this->y + (vY * velocity);
	}
};

player p;

void handleKey(Button_state b) {
	switch (b.keyCode) {
	case K_UP:
		printFormat(INFO, "UP %hu", b.state);
		p.vY = b.state == 1 ? 1 : 0;
		break;
	case K_RIGHT:
		printFormat(INFO, "RIGHT %hu",b.state);
		p.vX = b.state == 1 ? 1 : 0;
		break;
	case K_DOWN:
		printFormat(INFO, "DOWN %hu", b.state);
		p.vY = b.state == 1 ? -1 : 0;
		break;
	case K_LEFT:
		printFormat(INFO, "LEFT %hu", b.state);
		p.vX = b.state == 1 ? -1 : 0;
		break;
	case K_SPACE:
		printFormat(INFO, "SPACE %hu", b.state);
		break;
	}
}

void handleInput(Game_input* input) {
	Button_state b;
	while (input->front > 0) {
		b = input->pop();
		if (b.keyCode == 0) {
			break;
		}
		handleKey(b);

		
	}
}

void bouncingCube(Game* game) {
	static int srcX = 0;
	static int srcY = 0;
	static int destX = 100;
	static int destY = 100;
	static int vX = 1;
	static int vY = 1;
	const int speed = 10;
	
	


	drawRectangle(0, 0, 100, 100, 0x00FF0000);
	drawRectangle(100, 100, 200, 200, 0x00FF00FF);
	drawRectangle(200, 200, 300, 300, 0x00FFFF00);
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


void updateAndRender(Game* game) {
	
	handleInput(&(game->input));
	p.update();
	drawRectangle(0, 0, game->buffer.sizeX, game->buffer.sizeY, 0);
	drawRectangle(p.x, p.y, p.x+100, p.y + 100, 0x009342f5);

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

