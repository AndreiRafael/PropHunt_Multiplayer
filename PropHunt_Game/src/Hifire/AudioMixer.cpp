#include "AudioMixer.h"
#include <iostream>

AudioMixer* AudioMixer::instance = nullptr;

AudioMixer::AudioMixer()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}


AudioMixer::~AudioMixer()
{
}

AudioMixer* AudioMixer::GetInstance(){
	if (instance == nullptr)
		instance = new AudioMixer();
	return instance;
}

void AudioMixer::AddShort(char* audioName){
	shortArraySize ++;
	Short* newArray = new Short[shortArraySize];
	for (int i = 0; i < shortArraySize - 1; i++)	{
		newArray[i] = shorts[i];
	}
	delete[] shorts;
	shorts = new Short[shortArraySize];
	for (int i = 0; i < shortArraySize - 1; i++)	{
		shorts[i] = newArray[i];
	}
	delete[] newArray;

	shorts[shortArraySize - 1].audio = Mix_LoadWAV(audioName);
	if (shorts[shortArraySize - 1].audio == nullptr)
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	shorts[shortArraySize - 1].name = audioName;
}

int AudioMixer::GetShortID(char* p_name){
	for (int i = 0; i < shortArraySize; i++)	{
		if (shorts[i].name == p_name){
			return i;
		}
	}
	AddShort(p_name);
	return shortArraySize - 1;
}

