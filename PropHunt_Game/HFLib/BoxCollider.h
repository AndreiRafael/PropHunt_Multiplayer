#pragma once
#include "Component.h"
#include <SDL.h>
#include "LinkedLists.h"
#include <math.h>
class BoxCollider : public Component{
private:
	SDL_Rect myRect;
	SDL_Rect result;
	Vector2 prev;
	bool prevCol = false;
	bool colliding = false;
	float height, width, hHeight, hWidth;
	void Awake(){
		myRect = { 0, 0, 1, 1 };
		SetCollisionRectSize(1, 1);
		gameObject->SetCollider(this);
		prev = gameObject->position;
	}

	void Start(){

	}

	void Update(){
		myRect.x = (int)gameObject->position.x - (int)gameObject->scale.x * hWidth;
		myRect.y = (int)gameObject->position.y - (int)gameObject->scale.y * hHeight;
		prevCol = colliding;
		for (int i = 0; i < gameObject->scene->GetLayerCount(); i++){
			DoubleNodeList<GameObject*>* gameObjects = gameObject->scene->GetGameObjects(i);
			for (DoubleNode<GameObject*>* itr = gameObjects->m_head; itr != nullptr; itr = itr->m_nextNode){
				if (itr->m_data->GetCollider() != nullptr && itr->m_data != this->gameObject){
					if (SDL_IntersectRect(&myRect, &itr->m_data->GetCollider()->GetCollisionRect(), &result) == SDL_TRUE){
						colliding = true;
						gameObject->SetPosition(prev);
					}
				}
			}
		}
		if (!colliding)
			prev = gameObject->position;
	}
	

	void Render(){
		/*SDL_SetRenderDrawColor(GAME_MANAGER->GetRenderer(), 255, 0, 0, 255);
		SDL_RenderDrawRect(GAME_MANAGER->GetRenderer(), &myRect);*/
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
};