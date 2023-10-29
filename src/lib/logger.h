#pragma once

enum level {
	INFO = 1,
	DEBUG = 2,
	ERROR = 3
};

void print(level level, const char* message);
// 1 = info, 2 = debug, 3 = error

void printFormat(level level, const char* format, ...);
// 1 = info, 2 = debug, 3 = error