#pragma once
#include "logger.h"
#include "uchu.h"
#include <unordered_map>

struct Buffer;
struct Button_state;
struct Game_input;
struct Game;




int createWindow(int x,int y, int width,int height, const char* title, Game* game);
int loop(Game* game);
int drawRectangle(int srcX, int srcY, int destX, int destY, int color);
