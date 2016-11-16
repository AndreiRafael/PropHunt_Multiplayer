#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;
TextureManager * TextureManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new TextureManager();
		instance->Start();
	}
	return instance;
}

void TextureManager::Start() {
	textures = new std::vector<Texture*>(0);
	surface = nullptr;
}