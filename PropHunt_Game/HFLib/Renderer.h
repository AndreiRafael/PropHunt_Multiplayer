#pragma once
#include "Component.h"
#include <SDL.h>
#include "GameManager.h"
#include "TextureManager.h"

class Renderer : public Component{
private:
	//-the id of the renderer texture
	int textureID = -1;
	//-the rect of the image that will be drawn
	SDL_Rect imgRect;
	//the rect where the image will be drawn
	SDL_Rect destRect;

	void Awake(){
		imgRect = { 0, 0, 0, 0 };
		gameObject->SetRenderer(this);
	}

	void Start(){

	}

	void Update(){
		
	}

	void Render(){
		destRect.x = (int)-gameObject->scene->camera.x + (int)(gameObject->position.x + (float)GAME_MANAGER->hWidth - (gameObject->scale.x * (float)imgRect.w / 2.0f));
		destRect.y = (int)gameObject->scene->camera.y + (int)(-gameObject->position.y + (float)GAME_MANAGER->hHeight - (gameObject->scale.y * (float)imgRect.h / 2.0f));
		destRect.w = (int)((float)imgRect.w * gameObject->scale.x);
		destRect.h = (int)((float)imgRect.h * gameObject->scale.y);
		if (gameObject->position.x > gameObject->scene->camera.x - GAME_MANAGER->hWidth - destRect.w) {
			if (gameObject->position.x < gameObject->scene->camera.x + GAME_MANAGER->hWidth + destRect.w) {
				if (gameObject->position.y > gameObject->scene->camera.y - GAME_MANAGER->hHeight - destRect.h) {
					if (gameObject->position.y < gameObject->scene->camera.y + GAME_MANAGER->hHeight + destRect.h) {
						SDL_RenderCopy(GAME_MANAGER->GetRenderer(), TEXTURES->textures->at(textureID)->tex, &imgRect, &destRect);
					}
				}
			}
		}
	}

public:
	void SetTexture(std::string textureName){
		textureID = TEXTURES->GetTextureID(("Assets/" + textureName).c_str());
		DivideTiles(1, 1);
	}

	void SetTexture(int id){
		textureID = id;
		DivideTiles(1, 1);
	}

	void DivideTiles(int horizontalTiles, int verticalTiles){
		imgRect.w = TEXTURES->GetTextureByID(textureID)->w / horizontalTiles;
		imgRect.h = TEXTURES->GetTextureByID(textureID)->h / verticalTiles;
	}

	void SetTileCoordinates(int x, int y){
		imgRect.x = x * imgRect.w;
		imgRect.y = y * imgRect.h;
	}

	int GetWidth(){
		return imgRect.w;
	}

	int GetHeight(){
		return imgRect.h;
	}
};