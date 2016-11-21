#pragma once
#include <HifireLibrary.h>
#include "../InputConfig.h"

class DynamicTexture : public Component{
private:
	int atualSprite = 0;
	int max = 20;
public:
	UDPComponent* udpComp;
	Renderer* rend;
	//Mulai disebut pada awal adegan
	void Start(){
		// mendaftar kunci yang
		/*HF_INPUT->AddButton();
		HF_INPUT->AddKeyToButton(SDLK_e);
		HF_INPUT->AddButton();
		HF_INPUT->AddKeyToButton(SDLK_q);*/
		rend = GetComponent<Renderer>();
	}

	//update dipanggil sekali saban membingkai
	void Update(){
		//memeriksa entri yang
		if (HF_INPUT->GetButtonDown(hfInput::nextSprite))
		{
			atualSprite++;
			ChangeTexture();
		}
		if (HF_INPUT->GetButtonDown(hfInput::prevSprite))
		{
			atualSprite--;
			ChangeTexture();
		}
	}

	void DynamicTexture::ChangeTexture()
	{
		if (atualSprite >= max)
			atualSprite = 0;
		if (atualSprite < 0)
			atualSprite = max - 1;
		rend->SetTexture(atualSprite);
		gameObject->GetCollider()->FitSprite();
		//enviar para o server
		Command cmd;
		cmd.commandType = PH_CMD::sprite;
		cmd.playerID = udpComp->meuID;
		sendto(udpComp->meuSocket, (const char*)&cmd, 50, NULL, (SOCKADDR*)&udpComp->server, sizeof(sockaddr_in));

		SpriteCommand spriteCmd;
		spriteCmd.playerID = udpComp->meuID;
		spriteCmd.spriteID = atualSprite;
		sendto(udpComp->meuSocket, (const char*)&spriteCmd, 50, NULL, (SOCKADDR*)&udpComp->server, sizeof(sockaddr_in));
	}
};