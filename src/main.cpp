// uchu-p.cpp : définit le point d'entrée de l'application.
//

#include "logger.h"
#include "graphic.h"
using namespace std;

int main()
{
	print(INFO, "HELLO");
	print(DEBUG, "HELLO");
	print(ERROR, "HELLO");

	createWindow(100, 100,800,600, "Uchu Game");

	return 0;
}
