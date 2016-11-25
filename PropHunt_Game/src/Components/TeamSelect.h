#pragma once
#include <HifireLibrary.h>
#include <UDPComponent.h>
#include "..\InputConfig.h"

class TeamSelect : public Component{
public:
	GameObject* hud;
	GameObject* victCheck;
	UDPComponent* udpComp;
	float startTimer = 15.0f;
	int team = -1;
	//Start is called at the start of a scene
	void Start(){
		gameObject->SetActive(false);
	}

	//Update is called once per frame
	void Update(){
		if (team == -1){
			if (HF_INPUT->GetButtonDown(hfInput::nextSprite)){//escolheu hunter
				team = 1;
			}
			else if (HF_INPUT->GetButtonDown(hfInput::prevSprite)){//escolheu prop
				team = 0;
			}
		}

		if (team >= 0){
			/*Command cmd;
			cmd.commandType = PH_CMD::team;
			cmd.playerID = udpComp->meuID;
			sendto(udpComp->meuSocket, (const char*)&cmd, 50, NULL, (SOCKADDR*)&udpComp->server, sizeof(sockaddr_in));
			*/
			TeamCommand teamCmd;
			teamCmd.playerID = udpComp->meuID;
			teamCmd.cmdType = PH_CMD::team;
			teamCmd.team = team;
			sendto(udpComp->meuSocket, (const char*)&teamCmd, 50, NULL, (SOCKADDR*)&udpComp->server, sizeof(sockaddr_in));
			
			switch (team){
			case 0://prop
				udpComp->propArray[udpComp->meuID]->SetActive(true);
				udpComp->propArray[udpComp->meuID]->GetRawComponent(0)->SetEnabled(true);
				udpComp->propArray[udpComp->meuID]->GetRawComponent(1)->SetEnabled(true);
				udpComp->propArray[udpComp->meuID]->GetComponent<LifeManager>()->SetEnabled(true);
				udpComp->propArray[udpComp->meuID]->GetComponent<LifeManager>()->hud = hud;
				udpComp->propArray[udpComp->meuID]->GetComponent<LifeManager>()->UpdateText();
				gameObject->GetComponent<HudRenderer>()->SetEnabled(false);
				break;
			case 1://hunter
				udpComp->hunterArray[udpComp->meuID]->SetActive(true);
				udpComp->hunterArray[udpComp->meuID]->GetRawComponent(0)->SetEnabled(true);
				udpComp->hunterArray[udpComp->meuID]->GetRawComponent(1)->SetEnabled(true);
				udpComp->hunterArray[udpComp->meuID]->GetComponent<LifeManager>()->SetEnabled(true);
				udpComp->hunterArray[udpComp->meuID]->GetComponent<LifeManager>()->hud = hud;
				udpComp->hunterArray[udpComp->meuID]->GetComponent<LifeManager>()->UpdateText();
				gameObject->GetComponent<HudRenderer>()->SetTexture("sprintes/apres/three.png");

				break;
			}
			team = -2;
		}
		
		startTimer -= COUNTER->DeltaTime();
		if (team == -2){
			if (startTimer <= 0.0f){
				gameObject->SetActive(false);
				victCheck->SetActive(true);
			}
		}
	}
};