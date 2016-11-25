#pragma once
#include <HifireLibrary.h>
#include <UDPComponent.h>

class UDPComponent;
class LifeManager : public Component{
private:
	//Start is called at the start of a scene
	void Start(){
		SetEnabled(false);
	}

	//Update is called once per frame
	void Update(){
		if (HF_INPUT->GetMouseButtonDown(3)){
			for (int i = 0; i < NUM_PLAYERS; i++){
				std::cout << "hunter_" << i << udpComp->hunterArray[i]->GetComponent<LifeManager>()->life << std::endl;
				std::cout << "prop_" << i << udpComp->propArray[i]->GetComponent<LifeManager>()->life << std::endl;
			}
		}
	}
public:
	float life = 30.0f;
	GameObject* hud = nullptr;
	UDPComponent* udpComp;

	void TakeDamage(float amount){
		if (isEnabled()){
			life -= amount;
			UpdateText();
			//se desativa caso perca toda avida
			if (life <= 0.0f)
				gameObject->SetActive(false);
			//manda a nova vida para o server
			/*Command cmd;
			cmd.commandType = PH_CMD::life;
			cmd.playerID = udpComp->meuID;
			sendto(udpComp->meuSocket, (const char*)&cmd, 50, NULL, (SOCKADDR*)&udpComp->server, sizeof(sockaddr_in));
			*/

			LifeCommand lifeCmd;
			lifeCmd.playerID = udpComp->meuID;
			lifeCmd.cmdType = PH_CMD::life;
			lifeCmd.life = life;
			sendto(udpComp->meuSocket, (const char*)&lifeCmd, 50, NULL, (SOCKADDR*)&udpComp->server, sizeof(sockaddr_in));
		}
	}

	void UpdateText(){
		if (hud != nullptr){
			std::string str = "HP:" + std::to_string((int)life);
			hud->GetComponent<HudText>()->SetText(str);
		}
	}
};