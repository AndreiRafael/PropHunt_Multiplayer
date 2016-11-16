#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "Input.h"

class Button : public Component{
private:
	BoxCollider* collider;
	void(*function)() = nullptr;
	SceneManager* sceneToLoad;

	void Awake(){
		gameObject->AddComponent<BoxCollider>();
		collider = GetComponent<BoxCollider>();
	}

	void Start(){

	}

	void Update(){
		
	}
public:
	bool isClicked(){
		int x, y;
		HF_INPUT->GetMousePosition(&x, &y);

		if (x > gameObject->position.x - collider->GetCollisionRect().w / 2 &&
			x < gameObject->position.x + collider->GetCollisionRect().w / 2 &&
			y > gameObject->position.y - collider->GetCollisionRect().h / 2 &&
			y < gameObject->position.y + collider->GetCollisionRect().h / 2 &&
			HF_INPUT->GetMouseButtonDown(SDL_BUTTON_LEFT)){
			if (function != nullptr)
				function();
			return true;
		}
		return false;
	}

	void SetSize(int w, int h){
		collider->SetCollisionRectSize(w, h);
	}

	void SetFunctionCall(void(*func)()){
		function = func;
	}
};