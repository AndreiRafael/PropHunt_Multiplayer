#include <iostream>
#include <HifireLibrary.h>
#include "Scenes\SC_Gameplay.h"
#include "Scenes\SC_Menu.h"
#include "InputConfig.h"
std::vector<BoxCollider*> BoxCollider::allColliders;
int main(int argc, char** argv)
{
	//SDL_DisplayMode display;
	//pra fazer auto-resize depois
	GAME_MANAGER->Initialize("Multiplayer ", 800, 600, SDL_WINDOW_OPENGL, "2");
	//HF_INPUT->LoadDefaultButtons();
	InputConfig::Config();
	
	GAME_MANAGER->LoadScene<SC_Gameplay>();
	GAME_MANAGER->Begin();
	GAME_MANAGER->ForceQuit();
	return 0;
}