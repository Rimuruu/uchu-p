// uchu-p.cpp : définit le point d'entrée de l'application.
//

#include "logger.h"
#include "graphic.h"
#include "uchu.h"
#include "time.h"
#include <stdio.h>
#include "sound.h"



using namespace std;

const int WIDTH = 600;
const int HEIGHT = 800;
const char* title = "Uchu Game";
short RUNNING = 1;

const char * fileSounds[] = { "./assets/sound/shoot.wav","./assets/sound/shoot2.wav"};




int main()
{
	Buffer buffer = Buffer(WIDTH, HEIGHT);
	Game_input input = Game_input();
	Game game{ buffer,input };

	loadImageBMP("./assets/img/t.bmp");
	
	createWindow(100, 100,WIDTH,HEIGHT, title, &game);
	initSound(fileSounds,2);
	loop(&game);
	cleanup();


	return 0;
}


