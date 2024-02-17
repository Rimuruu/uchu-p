#include "sound.h"
#define UNICODE
#include <windows.h>
#include <xaudio2.h>
#include <vector>
#include <stdio.h>
#include <string.h>

constexpr int NUM_CHANNELS = 2;
constexpr int SAMPLE_RATE = 44100;
constexpr int MAX_SOUNDS = 10;

IXAudio2* pXAudio2;
IXAudio2MasteringVoice* pMasterVoice;


struct xAudioVoice : IXAudio2VoiceCallback
{
    IXAudio2SourceVoice* voice = nullptr;
   
    float fadeTimer;
    char* soundPath;

    int playing=false;

    void OnStreamEnd() noexcept
    {
        voice->Stop();
        playing = false;
    }

    void OnBufferStart(void* pBufferContext) noexcept
    {
        playing = true;
    }

    void OnVoiceProcessingPassEnd() noexcept {}
    void OnVoiceProcessingPassStart(UINT32 SamplesRequired) noexcept {}
    void OnBufferEnd(void* pBufferContext) noexcept {}
    void OnLoopEnd(void* pBufferContext) noexcept {}
    void OnVoiceError(void* pBufferContext, HRESULT Error) noexcept {}
};


struct Sound {
    WAVFile* file = nullptr;
    boolean isPlaying = false;


};


// hasmap of sound

std::unordered_map<unsigned int, Sound> sounds;
xAudioVoice voices[MAX_SOUNDS];
WAVEFORMATEX wfx;

// Function to load a WAV file into memory
WAVFile* LoadWAV(const char* filePath)
{
    WAVFile* fileW = nullptr;
    char * buffer = nullptr;
    
    int fileSize = 0;
    auto file = fopen(filePath, "rb");
    if(!file)
    {
         return nullptr;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = (char *) malloc(sizeof(char)*(fileSize));
    memset(buffer, 0, fileSize + 1);
    fread(buffer, sizeof(char), fileSize, file);

    fclose(file);
    fileW = (WAVFile*) buffer;
     return fileW;
}

void playSound(unsigned a) {
    static int i = 0;
       Sound s = sounds.at(a);

    // Submit buffer and start playing
    XAUDIO2_BUFFER buffer = {};
    buffer.pAudioData = (BYTE *) &(s.file->dataBegin);
    buffer.AudioBytes = static_cast<UINT32>(s.file->header.dataChunkSize);
    buffer.Flags = XAUDIO2_END_OF_STREAM;
    buffer.LoopCount =  0;

    
    xAudioVoice* voice = nullptr;
    
    for (int v = 0; v < MAX_SOUNDS; v++) {
        if (voices[v].playing == false) {
            voice = voices + v;
            break;
        
        }

    }

    if (voice == nullptr) return;

    HRESULT hr = voice->voice->SubmitSourceBuffer(&buffer);
    printFormat(DEBUG, "%b", SUCCEEDED(hr));

    if (SUCCEEDED(hr))
        hr = voice->voice->Start(0);

}

void loadSound(const char* sf , unsigned int a)  {


        Sound s;
        s.file = LoadWAV(sf);
        std::pair<unsigned int, Sound> pair(a, s);
        if(s.file) sounds.insert(pair);
          
   

}

void freeSounds() {
     for (auto& it : sounds) {
        
         Sound s = it.second;
         
         if (s.file != nullptr) free(s.file);

    }
}

void freeVoices() {
     for (int i = 0; i < MAX_SOUNDS; i++) {

        xAudioVoice pSourceVoice = voices[i];
        if (voices[i].voice) {
            voices[i].voice->DestroyVoice();
        }
    }


}

void initXaudio2() {
    // Initialize COM
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    wfx.wFormatTag = 1;
    wfx.nChannels = NUM_CHANNELS;
    wfx.nSamplesPerSec = SAMPLE_RATE;
    wfx.wBitsPerSample = 16;
    wfx.nBlockAlign = (NUM_CHANNELS * wfx.wBitsPerSample) / 8;
    wfx.nAvgBytesPerSec = SAMPLE_RATE * wfx.nBlockAlign;


    // Create XAudio2 engine
     HRESULT hr = XAudio2Create(&pXAudio2);
    if (FAILED(hr))
    {
        CoUninitialize();
        return;
    }

    // Create mastering voice
    hr = pXAudio2->CreateMasteringVoice(&pMasterVoice);
    if (FAILED(hr))
    {
        pXAudio2->Release();
        CoUninitialize();
        return;
    }

    

    // Create source voice
    for (int i = 0; i < MAX_SOUNDS; i++) {

        voices[i];
        hr = pXAudio2->CreateSourceVoice(&voices[i].voice, &wfx, 0, XAUDIO2_DEFAULT_FREQ_RATIO, voices + i , nullptr, nullptr);
        voices[i].voice->SetVolume(0.20f);
        if (FAILED(hr))
        {
        freeSounds();
        freeVoices();
        pMasterVoice->DestroyVoice();
        pXAudio2->Release();
        CoUninitialize();
        return;
        }

    }
    
    
  
    
        



}

void cleanup() {
    // Cleanup
    pMasterVoice->DestroyVoice();
    pXAudio2->Release();
    CoUninitialize();
    freeSounds();
    freeVoices();

}

void initSound(){


    

    initXaudio2();

   



}



