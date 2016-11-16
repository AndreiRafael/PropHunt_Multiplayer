#pragma once
#include "Component.h"
#include "AudioMixer.h"

class AudioSouce : public Component{
private:
	int audioID;

	void Awake(){

	}

	void Start(){

	}

	void Update(){

	}
public:
	void SetAudio(char* audioName){
		audioID = AUDIO_MIXER->GetShortID(audioName);
	}

	void Play(){
		Mix_PlayChannel(-1, AUDIO_MIXER->shorts[audioID].audio, 0);
	}
};