#pragma once
#include <SDL.h>
#include "LinkedLists.h"
#include "GameManager.h"
#include <iostream>
#define HF_INPUT Input::GetInstance()

enum InputButtonList{
	hfb_up,
	hfb_down,
	hfb_left,
	hfb_right,
	hfb_jump,
	hfb_fire
};
class Vector2;
class InputButton{
private:
	bool prev = false;
	bool isDown = false;

public:
	SimpleNodeList<int>* keyList;
	InputButton(){
		keyList = new SimpleNodeList<int>;
	}
	void AddKey(SDL_Keycode key){
		keyList->Append(key);
	}
	void Check(){
		SimpleNodeListIterator<int> itr = keyList->GetIterator();
		bool done = false;
		while (itr.Valid() && !done){
			if (GAME_MANAGER->GetEvent()->type == SDL_KEYDOWN){
				if (GAME_MANAGER->GetEvent()->key.keysym.sym == itr.Item()){
					isDown = true;
					done = true;
				}
			}
			else if (GAME_MANAGER->GetEvent()->type == SDL_KEYUP){
				if (GAME_MANAGER->GetEvent()->key.keysym.sym == itr.Item()){
					isDown = false;
					done = true;
				}
			}
			itr.Forth();
		}
	}

	bool Released(){
		return (!isDown && isDown != prev);
	}

	bool Pressed(){
		return (isDown && isDown != prev);
	}

	bool Holding(){
		return isDown;
	}

	void PreUpdate() {
		prev = isDown;
	}

	void Update(){
		Check();
	}
};

class Input
{
	friend class InputButton;
private:

	bool flushKeyDown = false;//should we flush keydown?
	bool flushKeyUp = false;//should we flush keyup?

	bool flushMouseDown = false;//should we flush Mousedown?
	bool flushMouseUp = false;//should we flush Mouseup?

	bool flushMouseWheel = false;//should we flush MouseWheel?

	int times = 0;
public:
	~Input();
	static Input* instance;
	static Input* GetInstance();

	void HideCursor();
	void ShowCursor();

	void GetMousePosition(int* x, int* y);
	void GetMousePosition(Vector2* vec);
	void GetMouseScreenPosition(int* x, int* y);
	bool GetMouseButtonDown(int button);
	bool GetMouseButtonUp(int button);
	bool GetMouseButton(int);
	void CheckButton(int);
	void CheckButton(int, bool);

	//Buttons from class up above

	InputButton* buttons;
	int buttonCount = 0;
	void AddButton();
	void AddKeyToButton(SDL_Keycode, int);
	void AddKeyToButton(SDL_Keycode);
	//Loads Some default buttons to the code
	void LoadDefaultButtons();

	//Input Functions

	bool GetButtonDown(int);
	bool GetButtonUp(int);
	bool GetButton(int);

	float GetMouseScrollWheel();
	bool GetMouseScrollWheelDown();
	bool GetMouseScrollWheelUp();

	void StartLoop() {
		e->wheel.y = 0.0f;
		for (int i = 0; i < 3; i++)
			mousePrev[i] = mouseButtons[i];
		for (int i = 0; i < buttonCount; i++) {
			buttons[i].PreUpdate();
		}
	}

	void Update(){
		times++;
		if (GAME_MANAGER->GetEvent()->type == SDL_QUIT)
			GAME_MANAGER->ForceQuit();
		for (int i = 0; i < 3; i++)
			CheckButton(i + 1);

		for (int i = 0; i < buttonCount; i++){
			buttons[i].Update();
		}
	}

	void Clear() {
		
	}

private:
	SDL_Event* e;

	bool mouseButtons[3];
	bool mousePrev[3];
	int mouseX, mouseY;

	Input();
};

