#pragma once
#include <Input.h>

enum hfInput{
	up,
	down,
	right,
	left,
	nextSprite,
	prevSprite
};
namespace InputConfig{
	void Config(){
		HF_INPUT->AddButton();//up
		HF_INPUT->AddKeyToButton(SDLK_w);
		HF_INPUT->AddButton();//down
		HF_INPUT->AddKeyToButton(SDLK_s);
		HF_INPUT->AddButton();//right
		HF_INPUT->AddKeyToButton(SDLK_d);
		HF_INPUT->AddButton();//left
		HF_INPUT->AddKeyToButton(SDLK_a);
		HF_INPUT->AddButton();//troca sprite +
		HF_INPUT->AddKeyToButton(SDLK_e);
		HF_INPUT->AddButton();//troca sprite -
		HF_INPUT->AddKeyToButton(SDLK_q);
	}
}