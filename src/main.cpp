﻿// uchu-p.cpp : définit le point d'entrée de l'application.
//

#include "logger.h"
#include "graphic.h"
#include "uchu.h"
#include "time.h"
#include <stdio.h>



using namespace std;

const int WIDTH = 600;
const int HEIGHT = 800;
const char* title = "Uchu Game";
short RUNNING = 1;

int main()
{
	Buffer buffer = Buffer(WIDTH, HEIGHT);
	Game_input input = Game_input();
	Game game{ buffer,input };

	print(INFO, "HELLO");
	print(DEBUG, "HELLO");
	print(ERROR, "HELLO");

	createWindow(100, 100,WIDTH,HEIGHT, title, &game);
	loop(&game);



	return 0;
}


