#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Counter.h"

#define GAME_MANAGER GameManager::GetInstance()

class SceneManager;
class GameManager{
private:
	GameManager();
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* e;
	static GameManager* instance;
	bool quit = false;

	//the currently loaded scene
	bool changeScene = false;
	SceneManager* nextScene = nullptr;
	SceneManager* loadedScene = nullptr;

public:	
	~GameManager();

	void Initialize(char* p_title, int p_x, int p_y, SDL_WindowFlags flag);
	void Initialize(char* p_title, int p_x, int p_y, SDL_WindowFlags flag, const char* LVL);
	void Initialize(char* p_title, SDL_WindowFlags flag);
	void Begin();
	void Update();

	//Scene Functions
	void ChangeScene();


	template<class T>
	void LoadScene() {
		changeScene = true;
		T* tempScene = new T;
		nextScene = tempScene;
	}

	bool Quit();
	void ForceQuit();

	//sdl Stuff

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	SDL_Event* GetEvent();
	int width, height, hWidth, hHeight;

	SceneManager* GetLoadedScene();

	//Singleton
	static GameManager* GetInstance();

	//setter
	void SetBackgroundColor(int r, int g, int b);
};