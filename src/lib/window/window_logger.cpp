#include "logger.h"
#include <iostream>
#include <sstream>
#include <time.h>

const char* get_timedate() {
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char* formatted = asctime(tm);
	if (!formatted) return "";
	size_t length = strlen(formatted);
	if (length > 0 && formatted[length - 1] == '\n') {
		formatted[length - 1] = '\0'; 
	}

	char* time = new char[length];
	strcpy(time, formatted);
	return time;
}

void print(level level,const char* message) {
	const char* time = get_timedate();
	switch (level) {
	case INFO:
		std::cout << time << " " << "[INFO] : " << message << std::endl;
		break;
	case DEBUG:
		std::cout << time << " " << "[DEBUG] : " << message << std::endl;
		break;
	case ERROR:
		std::cout << time << " " << "[ERROR] : " << message << std::endl;
		break;
	default:
		std::cout << time << " " << message << std::endl;
	}
}