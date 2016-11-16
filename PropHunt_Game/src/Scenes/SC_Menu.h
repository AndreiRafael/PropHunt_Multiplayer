#pragma once
#include <HifireLibrary.h>

class SC_Menu : public SceneManager{
public:
	void ConfigureObjects();
	void OnSceneEnd();
private:
	//create GameObjects here...
};

//this function is called when the Scene is loaded
void SC_Menu::ConfigureObjects(){
	GAME_MANAGER->SetBackgroundColor(200, 200, 200);
	SetLayers(1);

}

//this is called when the scene is closed
void SC_Menu::OnSceneEnd(){
	
}