#pragma once
#include "Component.h"
#include <SDL.h>
#include "LinkedLists.h"
#include <math.h>
class BoxCollider : public Component{
private:
	static std::vector<BoxCollider*> allColliders;
	SDL_Rect myRect;
	SDL_Rect result;
	bool prevCol = false;
	bool colliding = false;
	bool autoCheck = false;
	float height, width, hHeight, hWidth;
	void Awake(){
		myRect = { 0, 0, 1, 1 };
		SetCollisionRectSize(1, 1);
		gameObject->SetCollider(this);
		allColliders.push_back(this);
	}

	void Update(){
		if (autoCheck)
			CheckCollision();
	}
public:
	void CheckCollision(){
		myRect.x = (int)gameObject->position.x - (int)gameObject->scale.x * hWidth;
		myRect.y = (int)gameObject->position.y - (int)gameObject->scale.y * hHeight;
		myRect.w = (int)(width * gameObject->scale.x);
		myRect.h = (int)(height * gameObject->scale.y);

		prevCol = colliding;
		colliding = false;
		for (int i = 0; i < allColliders.size(); i++){
			if (allColliders[i] != this){
				if (abs(allColliders[i]->gameObject->position.x - gameObject->position.x) < (allColliders[i]->GetCollisionRect().w + myRect.w) / 2){
					if (abs(allColliders[i]->gameObject->position.y - gameObject->position.y) < (allColliders[i]->GetCollisionRect().h + myRect.h) / 2){
						colliding = true;
						break;
					}
				}
			}
		}
	}
	

	void Render(){
		SDL_SetRenderDrawColor(GAME_MANAGER->GetRenderer(), 255, 0, 0, 255);
		SDL_RenderDrawRect(GAME_MANAGER->GetRenderer(), &myRect);
	}
public:
	SDL_Rect GetCollisionRect(){
		return myRect;
	}

	SDL_Rect GetSDLCollisionRect(){
		return result;
	}

	void SetCollisionRectSize(float w, float h){
		width = w;
		height = w;
		hWidth = h / 2.0f;
		hHeight = h / 2.0f;
	}

	void UpdateSize(){
		myRect.w = (int)(width * gameObject->scale.x);
		myRect.h = (int)(height * gameObject->scale.y);
	}

	bool InCollision(){
		return colliding;
	}

	bool EnteredCollision(){
		return (colliding && !prevCol);
	}

	bool ExitedCollision(){
		return (!colliding && prevCol);
	}

	void SetAutoCheck(bool state){
		autoCheck = state;
	}

	void FitSprite(){
		Renderer* rend = gameObject->GetRenderer();
		if (rend != nullptr){
			this->width = rend->GetWidth();
			this->height = rend->GetHeight();
			hHeight = height / 2.0f;
			hWidth = width / 2.0f;
			UpdateSize();
		}
	}
};

