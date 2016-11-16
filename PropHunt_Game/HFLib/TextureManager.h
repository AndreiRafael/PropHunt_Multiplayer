#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "GameManager.h"

#define TEXTURES TextureManager::GetInstance()

class Texture {
public:
	SDL_Texture* tex = nullptr;
	std::string name;
	int w, h;
	~Texture(){
		SDL_DestroyTexture(tex);
	}
};

class TextureManager
{
public:
	static int count;
	static TextureManager* instance;
	static TextureManager* GetInstance();

	SDL_Surface* surface;
	std::vector<Texture*>* textures;

	void ClearTextures() {
		for (int i = 0; i < (int)textures->size(); i++) {
			delete textures->at(i);
		}
		textures->clear();
		textures->resize(0);
	}

	void AddTexture(std::string name) {
		textures->resize(textures->size() + 1);
		surface = IMG_Load(name.c_str());
		if (surface != NULL) {
			textures->at(textures->size() - 1) = new Texture;
			textures->at(textures->size() - 1)->tex = SDL_CreateTextureFromSurface(GAME_MANAGER->GetRenderer(), surface);
			textures->at(textures->size() - 1)->name = name;
			textures->at(textures->size() - 1)->h = surface->h;
			textures->at(textures->size() - 1)->w = surface->w;
			SDL_FreeSurface(surface);
		}
	}

	SDL_Texture* GetSDLTextureByID(int texID) {
		if (texID < textures->size() && texID >= 0)
			return textures->at(texID)->tex;
		std::cout << "You are trying to access an inexistant texture" << std::endl;
		return nullptr;
	}

	Texture* GetTextureByID(const int texID) {
		if (texID < textures->size() && texID >= 0)
			return textures->at(texID);
		std::cout << "You are trying to access an inexistant texture" << std::endl;
		return textures->at(0);
	}

	SDL_Texture* GetTextureByName(std::string p_name) {
		for (int i = 0; i < textures->size(); i++){
			if (std::strcmp(textures->at(i)->name.c_str(), p_name.c_str()) == 0) {
				return textures->at(i)->tex;
			}
		}
		AddTexture(p_name);
		return textures->at(textures->size() - 1)->tex;
	}

	int GetTextureID(std::string p_name) {
		for (int i = 0; i < textures->size(); i++) {
			if (std::strcmp(textures->at(i)->name.c_str(), p_name.c_str()) == 0) {
				return i;
			}
		}
		AddTexture(p_name);
		return textures->size() - 1;
	}
private:
	void Start();
};

