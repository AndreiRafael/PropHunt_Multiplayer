#pragma once
#include <HifireLibrary.h>
#include <UDPComponent.h>

class VictoryCheck : public Component{
public:
	UDPComponent* udpComp;
	HudRenderer* rend;
private:
	bool ended = false;

	bool HuntWon(){
		bool propsDead = true;
		for (int i = 0; i < NUM_PLAYERS; i++){
			if (udpComp->propArray[i]->IsActive())
				propsDead = false;
		}
		if (propsDead){
			for (int i = 0; i < NUM_PLAYERS; i++){
				if (udpComp->hunterArray[i]->IsActive())
					return true;
			}
		}
		return false;
	}

	bool PropWon(){
		bool huntersDead = true;
		for (int i = 0; i < NUM_PLAYERS; i++){
			if (udpComp->hunterArray[i]->IsActive())
				huntersDead = false;
		}
		if (huntersDead){
			for (int i = 0; i < NUM_PLAYERS; i++){
				if (udpComp->propArray[i]->IsActive())
					return true;
			}
		}
		return false;
	}
	//Start is called at the start of a scene
	void Start(){
		rend = GetComponent<HudRenderer>();
		rend->SetEnabled(false);
		rend->SetTexture("sprintes/apres/huntWin.png");
	}

	//Update is called once per frame
	void Update(){
		if (!ended){
			if (HuntWon()){
				std::cout << "HuntWon" << std::endl;
				rend->SetEnabled(true);
				rend->SetTexture("sprintes/apres/huntWin.png");
				ended = true;
			}
			if (PropWon()){
				rend->SetEnabled(true);
				rend->SetTexture("sprintes/apres/propWin.png");
				ended = true;
			}
		}
	}
};