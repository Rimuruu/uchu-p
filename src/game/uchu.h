#pragma once
#include "key_binding.h"
#include "logger.h"
#include "graphic.h"
#include "ecs/ecs.h"
#include "entity/player.h"
#include "system/inputSystem.h"
#define BYTES_PER_PIXEL 4


typedef unsigned int u_int32;




struct Buffer {
	// RR GG BB
	void* memory;
	unsigned int sizeX;
	unsigned int sizeY;
	Buffer(unsigned int width, unsigned int height);
	~Buffer();
};



struct Button_state {
	u_int32 keyCode=0;
	short state; // 0 is released, 1 is pressed
 };

struct Node_button{
	Button_state val;
	Node_button* next;
	Node_button(Button_state val);
};

struct Game_input {
	Node_button* head;
	const static int size = 16;
	int front = 0;
	Button_state pop();
	void queue(Button_state key);
};

struct Game {
	Buffer buffer;
	Game_input input;
	Player* p;
	InputSystem is;
};


void init(Game* game);
void end(Game* game);

void updateAndRender(Game* game);
