#include <GameManager.h>
#include <SceneManager.h>
#include <Input.h>
#include <SDL_ttf.h>
#include <time.h>
#include <string>
#include <TextureManager.h>


GameManager* GameManager::instance = nullptr;

GameManager::GameManager(){
	e = new SDL_Event;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
}

GameManager::~GameManager(){
}

GameManager* GameManager::GetInstance(){
	if (instance == nullptr)
		instance = new GameManager();
	return instance;
}

SDL_Window* GameManager::GetWindow(){
	return window;
}

SDL_Renderer* GameManager::GetRenderer(){
	return renderer;
}

SDL_Event* GameManager::GetEvent(){
	return e;
}

void GameManager::Initialize(char* p_title, int p_x, int p_y, SDL_WindowFlags flag){
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_x, p_y, flag);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	width = p_x;
	height = p_y;
	hHeight = (int)((float)height / 2);
	hWidth = (int)((float)width / 2);
}


void GameManager::Initialize(char* p_title, int p_x, int p_y, SDL_WindowFlags flag, const char* LVL)
{
	Initialize(p_title, p_x, p_y, flag);
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, LVL)) std::cout << "Houve um erro ao aplicar o AntiAliasing."<<std::endl;
	else std::cout << "AntiAliasing x"<<LVL<<std::endl;
}

void GameManager::Initialize(char* p_title, SDL_WindowFlags flag){
	SDL_DisplayMode displayMode;
	if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0)
	{
		Initialize(p_title, displayMode.w, displayMode.h, flag);
	}
}

void GameManager::Begin(){
	while (!Quit()){
		//SDL_FlushEvents(SDL_KEYDOWN, SDL_MULTIGESTURE);
		Update();
	}
}

void GameManager::ChangeScene() {
	if (loadedScene != nullptr) {
		loadedScene->End();
		delete loadedScene;
	}
	loadedScene = nextScene;
	loadedScene->Start();

	changeScene = false;
}

void GameManager::Update(){
	//INPUT->Clear();
	if (changeScene)
		ChangeScene();

	COUNTER->SUpdate();

	HF_INPUT->StartLoop();
	//INPUT->Update();
	while (SDL_PollEvent(e) != 0)
		HF_INPUT->Update();
	//SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
	SDL_RenderClear(renderer);
	if (loadedScene != nullptr && loadedScene != NULL)
		loadedScene->Update();
	SDL_RenderPresent(renderer);
	COUNTER->EUpdate();

}

//scene functions
/*template<class T>
void GameManager::LoadScene(){
	if (loadedScene != nullptr) {
		loadedScene->End();
		delete loadedScene;
	}
	//T* tempScene = new T;
	//loadedScene = tempScene;
	//loadedScene->Start();
}*/

bool GameManager::Quit(){
	return quit;
}

void GameManager::ForceQuit(){
	quit = true;
}

SceneManager* GameManager::GetLoadedScene(){
	return loadedScene;
}

void GameManager::SetBackgroundColor(int r, int g, int b){
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}