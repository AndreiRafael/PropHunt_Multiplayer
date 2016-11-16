#pragma once
#include <SDL_mixer.h>
#define AUDIO_MIXER AudioMixer::GetInstance()
class AudioMixer
{
public:
	~AudioMixer();
	static AudioMixer* GetInstance();
	struct Short{
		Mix_Chunk* audio;
		char* name;
	};
	Short* shorts;
	int shortArraySize = 0;

	void AddShort(char*);
	int GetShortID(char*);
private:
	static AudioMixer* instance;

	AudioMixer();
};

