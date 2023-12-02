#include "sound.h"
#define UNICODE
#include <windows.h>



LPCWSTR ConvertToLPCWSTR(const char* text);


void playSound(const char* fileWav) {

	PlaySound(ConvertToLPCWSTR(fileWav), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
}