#pragma once
#include "Component.h"
#include <SDL.h>
#include "GameManager.h"
#include "TextureManager.h"

class HudRenderer : public Component {
private:
	//-the id of the renderer texture
	int textureID = -1;
	//-the rect of the image that will be drawn
	SDL_Rect imgRect;
	//the rect where the image will be drawn
	SDL_Rect destRect;
	//the start position
	Vector2 startPositon;

	void Awake() {
		imgRect = { 0, 0, 0, 0 };
	}

	void Start() {
		startPositon = gameObject->position;
		UpdatePosition();
	}

	void UpdatePosition() {
		destRect.x = (int)gameObject->position.x + GAME_MANAGER->width / 2 - (int)gameObject->scale.x * imgRect.w / 2;
		destRect.y = -(int)gameObject->position.y + GAME_MANAGER->height / 2 - (int)gameObject->scale.y * imgRect.h / 2;
		destRect.w = imgRect.w * gameObject->scale.x;
		destRect.h = imgRect.h * gameObject->scale.y;
	}

	

	

public:
	void Update() {
		if (startPositon != gameObject->position) {
			UpdatePosition();
		}
	}

	void Render() {
		SDL_RenderCopy(GAME_MANAGER->GetRenderer(), TEXTURES->textures->at(textureID)->tex, &imgRect, &destRect);
	}

	void SetTexture(std::string textureName) {
		textureID = TEXTURES->GetTextureID("Assets/" + textureName);
		DivideTiles(1, 1);
	}

	void DivideTiles(int horizontalTiles, int verticalTiles) {
		imgRect.w = TEXTURES->GetTextureByID(textureID)->w / horizontalTiles;
		imgRect.h = TEXTURES->GetTextureByID(textureID)->h / verticalTiles;
	}

	void SetTileCoordinates(int x, int y) {
		imgRect.x = x * imgRect.w;
		imgRect.y = y * imgRect.h;
	}
};