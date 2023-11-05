#pragma once
#include "logger.h"
#include "uchu.h"


struct Buffer;
int createWindow(int x,int y, int width,int height, const char* title, Buffer* buffer);
int loop(Buffer* buffer);
int drawRectangle(int srcX, int srcY, int destX, int destY, int color);