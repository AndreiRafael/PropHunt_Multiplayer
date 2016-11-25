#pragma once
#include <HifireLibrary.h>
#include <UDPComponent.h>

class UDPWeapon : public Component{
private:

public:
	UDPComponent* udpComp;
	//Start is called at the start of the scene
	void Start(){
		SetEnabled(false);
	}

	//update is called once per frame
	void Update(){
		if (HF_INPUT->GetMouseButtonDown(1)){
			std::cout << "tentei atirar" << std::endl;
			Vector2 mousePos;
			HF_INPUT->GetMousePosition(&mousePos);
			Vector2 dir = mousePos - gameObject->position;
			std::cout << dir.x << ", " << dir.y << std::endl;
			udpComp->currBullet = udpComp->currBullet + 1;
			if (udpComp->currBullet >= udpComp->maxBullets)
				udpComp->currBullet = 0;
			int i = udpComp->currBullet;
			dir.Normalize();
			udpComp->bullets[i]->GetComponent<Bullet>()->direction = dir;
			udpComp->bullets[i]->GetComponent<Bullet>()->shooter = this->gameObject;
			udpComp->bullets[i]->position = gameObject->position;
			udpComp->bullets[i]->SetActive(true);

			FireCommand fireCmd;
			fireCmd.playerID = udpComp->meuID;
			fireCmd.cmdType = PH_CMD::fire;
			fireCmd.posX = gameObject->position.x;
			fireCmd.posY = gameObject->position.y;
			fireCmd.dirX = dir.x;
			fireCmd.dirY = dir.y;
			sendto(udpComp->meuSocket, (const char*)&fireCmd, 50, NULL, (SOCKADDR*)&udpComp->server, sizeof(sockaddr_in));
		}
	}
};