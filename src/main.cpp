// uchu-p.cpp : définit le point d'entrée de l'application.
//

#include "logger.h"

using namespace std;

int main()
{
	print(INFO, "HELLO");
	print(DEBUG, "HELLO");
	print(ERROR, "HELLO");

	return 0;
}
