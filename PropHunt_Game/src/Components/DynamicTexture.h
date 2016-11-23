#pragma once
#include <HifireLibrary.h>
#include "../InputConfig.h"

class DynamicTexture : public Component{
private:
	int atualSprite = 12;
	int max = 20;
	BoxCollider* col;
public:
	UDPComponent* udpComp;
	Renderer* rend;
	//Mulai disebut pada awal adegan
	void Start(){
		rend = GetComponent<Renderer>();
		col = gameObject->GetCollider();
		ChangeTexture();
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
		
		col->FitSprite();
		col->SetCollisionRectSize(col->GetCollisionWidth(), col->GetCollisionHeight() / 2);
		col->SetCollisionOffset(0, -col->GetCollisionHeight() / 2.0f);

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