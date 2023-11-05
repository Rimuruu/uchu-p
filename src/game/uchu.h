#pragma once

#include "logger.h"
#include "graphic.h"
#define BYTES_PER_PIXEL 4


struct Buffer;
struct Buffer {
	// RR GG BB
	void* memory;
	unsigned int sizeX;
	unsigned int sizeY;
	Buffer(unsigned int width, unsigned int height);
	~Buffer();
};


void init(Buffer* buffer, unsigned int width, unsigned int height);
void updateAndRender(Buffer* buffer);
void end(Buffer* buffer);
