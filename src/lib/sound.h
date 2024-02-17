#include "logger.h"
#include <unordered_map>


#ifndef SOUND_H
#define SOUND_H

#pragma pack(push, 1)
struct WAVHeader
{
  // Riff Chunk
	unsigned int riffChunkId;
	unsigned int riffChunkSize;
	unsigned int format;

  // Format Chunk
	unsigned int formatChunkId;
	unsigned int formatChunkSize;
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned int sampleRate;
	unsigned int byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;

  // Data Chunk
	unsigned char dataChunkId[4];
	unsigned int dataChunkSize;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct WAVFile
{
	WAVHeader header;
	char dataBegin;
};
#pragma pack(pop)

void loadSound(const char* sf, unsigned int a);
void initSound();
void playSound(unsigned int a);
void cleanup();

#endif