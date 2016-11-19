#pragma once
#include <HifireLibrary.h>

class rafael : public Component{
private:
	bool go = false;
	//Start is called at the start of a scene
	void Start(){

	}

	//Update is called once per frame
	void Update(){
		go = !go;
		GAME_MANAGER->SetBackgroundColor(255, 255, 255);
		if (go){
			GAME_MANAGER->SetBackgroundColor(255, 0, 0);
		}
	}
};