#pragma once
#include "Component.h"
#include "GameManager.h"
#include <SDL_ttf.h>
#include "SceneManager.h"
#include <string>

class Text : public Component{
private:
	SDL_Rect destRect;
	SDL_Rect imgRect;
	SDL_Texture* m_texture = nullptr;
	SDL_Color color;
	TTF_Font* m_font = nullptr;
	int m_width, m_height;
	int m_hWidth, m_hHeight;

public:
	void Awake(){

	}

	void Start(){
		
	}

	void Update(){
		imgRect = { 0, 0, m_width, m_height };
		destRect.x = (int)-gameObject->scene->camera.x + (int)gameObject->position.x + GAME_MANAGER->hWidth - m_hWidth;
		destRect.y = (int)gameObject->scene->camera.y - (int)gameObject->position.y + GAME_MANAGER->hHeight - m_hHeight;
		destRect.w = imgRect.w;
		destRect.h = imgRect.h;
	}
	
	void Render(){
		if (m_texture != nullptr)
			SDL_RenderCopy(GAME_MANAGER->GetRenderer(), m_texture, &imgRect, &destRect);
	}

	void SetText(std::string p_text){
		if(m_texture != nullptr)
			SDL_DestroyTexture(m_texture);
		TEXTURES->surface = TTF_RenderText_Solid(m_font, p_text.c_str(), color);
		if (TEXTURES->surface != nullptr){
			m_texture = SDL_CreateTextureFromSurface(GAME_MANAGER->GetRenderer(), TEXTURES->surface);
			m_width = TEXTURES->surface->w;
			m_height = TEXTURES->surface->h;
			m_hWidth = (int)((float)m_width / 2.0f);
			m_hHeight = (int)((float)m_height / 2.0f);
		}
		SDL_FreeSurface(TEXTURES->surface);
	}

	void SetText(int p_text){
		std::string str = std::to_string(p_text);
		SetText(str);
	}

	void SetFont(std::string fontName, int fontSize){
		fontName = "Assets/" + fontName;
		m_font = TTF_OpenFont(fontName.c_str(), fontSize);
		if (m_font == nullptr)
			std::cout << "Erro ao carregar o arquivo de fonte";
	}

	void SetTextColor(int r, int g, int b){
		color.r = r;
		color.g = g;
		color.b = b;
	}
};