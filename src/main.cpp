// uchu-p.cpp : définit le point d'entrée de l'application.
//

#include "logger.h"
#include "graphic.h"
#include "uchu.h"
#include "time.h"
#include <stdio.h>



using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const char* title = "Uchu Game";
short RUNNING = 1;

int main()
{
	Buffer* buffer = new Buffer(WIDTH, HEIGHT);
	//time_t t = time(NULL);
	print(INFO, "HELLO");
	print(DEBUG, "HELLO");
	print(ERROR, "HELLO");
	init(buffer, WIDTH,HEIGHT);
	createWindow(100, 100,WIDTH,HEIGHT, title, buffer);
	loop(buffer);


	end(buffer);
	return 0;
}
