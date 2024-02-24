#pragma once
#include "key_binding.h"
#include "logger.h"
#include "graphic.h"
#include "ecs/ecs.h"
#include "entity/player.h"
#include "entity/bullet.h"
#include "system/system.h"
#include "level.h"
#define BYTES_PER_PIXEL 4

#ifndef UCHU_H
#define UCHU_H


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
	Level* l;
};


void init(Game* game);
void end(Game* game);
void nextLevel();
void updateAndRender(Game* game);

#endif // !UCHU_H

