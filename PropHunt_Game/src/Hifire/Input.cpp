#include "Input.h"
#include "SceneManager.h"
#include "Vector2.h"

Input* Input::instance = nullptr;

Input::Input()
{
	for (int i = 0; i < 4; i++)
		mouseButtons[i] = false;
	e = GAME_MANAGER->GetEvent();
}


Input::~Input()
{
}

Input* Input::GetInstance(){
	if (instance == nullptr)
		instance = new Input;
	return instance;
}

//gets the world position of the mouse cursor
void Input::GetMousePosition(int* x, int* y){
	int sdlX, sdlY;
	SDL_GetMouseState(&sdlX, &sdlY);
	*x = GAME_MANAGER->GetLoadedScene()->camera.x + sdlX - GAME_MANAGER->hWidth;
	*y = GAME_MANAGER->GetLoadedScene()->camera.y - sdlY + GAME_MANAGER->hHeight;
}

void Input::HideCursor(){
	SDL_ShowCursor(0);
}

void Input::ShowCursor(){
	SDL_ShowCursor(1);
}

//gets the world position of the mouse cursor and puts it into a vector2
void Input::GetMousePosition(Vector2* vec){
	int sdlX, sdlY;
	SDL_GetMouseState(&sdlX, &sdlY);
	vec->x = GAME_MANAGER->GetLoadedScene()->camera.x + sdlX - GAME_MANAGER->hWidth;
	vec->y = GAME_MANAGER->GetLoadedScene()->camera.y - sdlY + GAME_MANAGER->hHeight;
}

//gets the screen position of the mouse cursor, center is (0, 0)
void Input::GetMouseScreenPosition(int* x, int* y) {
	int sdlX, sdlY;
	SDL_GetMouseState(&sdlX, &sdlY);
	*x = sdlX - GAME_MANAGER->hWidth;
	*y = -sdlY + GAME_MANAGER->hHeight;
}

bool Input::GetMouseButtonDown(int button){
	//bool prev = mouseButtons[button - 1];
	//CheckButton(button);
	return ((mousePrev[button - 1] != mouseButtons[button - 1]) && !mousePrev[button - 1]);
}

bool Input::GetMouseButtonUp(int button){
	//bool prev = mouseButtons[button];
	//CheckButton(button);
	return ((mousePrev[button - 1] != mouseButtons[button - 1]) && mousePrev[button - 1]);
}

bool Input::GetMouseButton(int button){
	//CheckButton(button);
	return mouseButtons[button - 1];
}

void Input::CheckButton(int button) {
	if (GAME_MANAGER->GetEvent()->type == SDL_MOUSEBUTTONUP) {
		if (GAME_MANAGER->GetEvent()->button.button == button)
			CheckButton(button - 1, false);
	}
	if (GAME_MANAGER->GetEvent()->type == SDL_MOUSEBUTTONDOWN) {
		if(GAME_MANAGER->GetEvent()->button.button == button)
			CheckButton(button - 1, true);
	}
	
}

void Input::CheckButton(int button, bool state){
	mouseButtons[button] = state;
}

void Input::AddButton(){
	buttonCount += 1;
	InputButton* newArray = new InputButton[buttonCount];
	for (int i = 0; i < buttonCount - 1; i++)	{
		newArray[i] = buttons[i];
	}
	delete[] buttons;
	buttons = new InputButton[buttonCount];
	for (int i = 0; i < buttonCount - 1; i++)	{
		buttons[i] = newArray[i];
	}
	delete[] newArray;
}

void Input::AddKeyToButton(SDL_Keycode key, int button){
	buttons[button].AddKey(key);
}

void Input::AddKeyToButton(SDL_Keycode key){
	buttons[buttonCount - 1].AddKey(key);
}

//Loads Some default buttons to the code
void Input::LoadDefaultButtons(){
	AddButton();//hfb_up
	AddKeyToButton(SDLK_w, hfb_up);
	AddKeyToButton(SDLK_UP, hfb_up);
	AddButton();//hfb_down
	AddKeyToButton(SDLK_s, hfb_down);
	AddKeyToButton(SDLK_DOWN, hfb_down);
	AddButton();//hfb_left
	AddKeyToButton(SDLK_a, hfb_left);
	AddKeyToButton(SDLK_LEFT, hfb_left);
	AddButton();//hfb_right
	AddKeyToButton(SDLK_d, hfb_right);
	AddKeyToButton(SDLK_RIGHT, hfb_right);
	AddButton();//hfb_jump
	AddKeyToButton(SDLK_SPACE, hfb_jump);
	AddButton();//hfb_fire
	AddKeyToButton(SDLK_LCTRL, hfb_fire);
}

bool Input::GetButtonDown(int button){
	return buttons[button].Pressed();
}

bool Input::GetButtonUp(int button){
	return buttons[button].Released();
}

bool Input::GetButton(int button){
	return buttons[button].Holding();
}

float Input::GetMouseScrollWheel()
{
	if (e->type == SDL_MOUSEWHEEL) {
		return e->wheel.y;
	}
	return 0.0f;
}

bool Input::GetMouseScrollWheelUp()
{
	return GetMouseScrollWheel() > 0.5f;
}

bool Input::GetMouseScrollWheelDown()
{
	return GetMouseScrollWheel() < -0.5f;
}
