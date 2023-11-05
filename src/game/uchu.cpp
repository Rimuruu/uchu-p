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
	static int srcX = 0;
	static int srcY = 0;
	static int destX = 100;
	static int destY = 100;
	static int vX = 1;
	static int vY = 1;
	const int speed = 10;
	drawRectangle(0, 0, buffer->sizeX, buffer->sizeY, 0);


	drawRectangle(0,0,100,100,0x00FF0000);
	drawRectangle(100, 100, 200, 200, 0x00FF00FF);
	drawRectangle(200, 200, 300, 300, 0x00FFFF00);
	drawRectangle(srcX, srcY, destX, destY, 0x12386f);

	srcX = srcX + (vX * speed);
	srcY = srcY + (vY * speed);
	destX = destX + (vX * speed);
	destY = destY + (vY * speed);

	if (srcX <= 0 || destX >= buffer->sizeX) {
		vX = -vX;
	}
	if (srcY <= 0 || destY >= buffer->sizeY) {
		vY = -vY;
	}


}


void end(Buffer* buffer) {
	
	delete buffer;
}