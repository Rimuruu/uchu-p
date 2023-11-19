#include "uchu.h"
#include "component/box.h"
#include "component/position.h"
#include "ecs/ecs.h"

Buffer::Buffer(unsigned int width, unsigned int heigth) {
	this->sizeX = width;
	this->sizeY = heigth;


}

Buffer::~Buffer() {
	
}

Entity e;

void init() {
	e.addComponent<Position2D>(100,100);
	e.addComponent<Box>(200,200);
}

struct player {
	int x = 0;
	int y = 0;
	int v[2];
;
	int velocity = 10;
	int m[4];
	void update() {
		this->move();
		this->x = this->x + (v[0] * velocity);
		this->y = this->y + (v[1] * velocity);
		

	}
	void setMove(int dir,int state) {
		m[dir] = state;
	}
	void move() {
	
		v[1] = (m[0] ^ -m[1]) != 0xFFFFFFFE ? m[0] ^ -m[1] : 0;
		v[0] = (m[2] ^ -m[3]) != 0xFFFFFFFE ? m[2] ^ -m[3] : 0;
	}

	

};

player p;

void handleKey(Button_state b) {
	switch (b.keyCode) {
	case K_UP:
		printFormat(INFO, "UP %hu", b.state);
		p.setMove(0,b.state);
		break;
	case K_RIGHT:
		printFormat(INFO, "RIGHT %hu",b.state);
		p.setMove(2, b.state);
		break;
	case K_DOWN:
		printFormat(INFO, "DOWN %hu", b.state);
		p.setMove(1, b.state);
		break;
	case K_LEFT:
		printFormat(INFO, "LEFT %hu", b.state);
		p.setMove(3, b.state);
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
	e.render();
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

