#include "uchu.h"

typedef unsigned int u_int32;

Buffer::Buffer(unsigned int width, unsigned int heigth) {
	this->sizeX = width;
	this->sizeY = heigth;


}

Buffer::~Buffer() {
	
}

void init(Buffer* buffer, unsigned int width, unsigned int heigth) {
}

void updateAndRender(Buffer* buffer) {
	static u_int32 color = 0x00FF0000;
	u_int32* pixel = (u_int32*)buffer->memory;

	for (int x = 0; x < buffer->sizeX; x++) {
		for (int y = 0; y < buffer->sizeY; y++) {
			pixel[ x* buffer->sizeY + y] = color;
			
		}
		//color = x % 16 == 0 ? (color + 1) % 0x00FFFFF : color; //wtf ?
		color = (color + 0x00000001) % 0x00FFFFF;

	}
	


}


void end(Buffer* buffer) {
	
	delete buffer;
}