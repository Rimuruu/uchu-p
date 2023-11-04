#pragma once
#include "logger.h"
#include "uchu.h"



int createWindow(int x,int y, int width,int height, const char* title, Buffer* buffer);
int loop(Buffer* buffer);