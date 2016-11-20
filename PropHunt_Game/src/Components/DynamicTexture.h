#pragma once
#include <HifireLibrary.h>

class DynamicTexture : public Component{
private:
	int atualSprite = 0;
public:

	//Mulai disebut pada awal adegan
	void Start(){
		// mendaftar kunci yang
		HF_INPUT->AddButton();
		HF_INPUT->AddKeyToButton(SDLK_e);
		HF_INPUT->AddButton();
		HF_INPUT->AddKeyToButton(SDLK_q);
	}

	//update dipanggil sekali saban membingkai
	void Update(){
		//memeriksa entri yang
		if (HF_INPUT->GetButtonDown(0))
		{
			atualSprite++;
			ChangeTexture();
		}
		if (HF_INPUT->GetButtonDown(1))
		{
			atualSprite--;
			ChangeTexture();
		}
	}

	void DynamicTexture::ChangeTexture()
	{
		if (atualSprite > 0)atualSprite = 0;
		GetComponent<Renderer>()->SetTexture(atualSprite);
	}
};