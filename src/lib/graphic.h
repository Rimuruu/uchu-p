#include "logger.h"
#include <unordered_map>
#include <stdint.h>

#ifndef GRAPHIC_H
#define GRAPHIC_H
#define BMPHEADERSIZE 54


struct Buffer;
struct Button_state;
struct Game_input;
struct Game;

#pragma pack(push, 1)
struct BMPHeader {
	uint16_t headerField;
	unsigned int fileSize;
	uint16_t r1;
	uint16_t r2;
	unsigned int offset;




};
#pragma pack(pop)

#pragma pack(push, 1)
struct DIBHeader {
	unsigned int size;
	unsigned int width;
	unsigned int height;
	uint16_t planes;
	uint16_t bitCount;
	unsigned int compression;
	unsigned int imageSize;
	unsigned int xpixelsPerM;
	unsigned int YpixelsPerM;
	unsigned int ColorsUsed;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t re;
};
#pragma pack(pop)



#pragma pack(push, 1)
struct BMPFile {
	BMPHeader header;
	DIBHeader infoHeader;
	Color* table; // t = bitCount * 4
	char* data; // sizeof(data) =  imageSize


};
#pragma pack(pop)





BMPFile* loadImageBMP(const char* filePath);
int loadImage(const char* filePath,unsigned int a );
int drawImage(int destX, int destY, unsigned int a);

int createWindow(int x,int y, int width,int height, const char* title, Game* game);
int loop(Game* game);
int drawRectangle(int srcX, int srcY, int destX, int destY, int color);
int cleanupImage();
#endif // !GRAPHIC_H


