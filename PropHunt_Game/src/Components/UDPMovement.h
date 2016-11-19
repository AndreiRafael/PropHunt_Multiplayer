#pragma once
#include <HifireLibrary.h>
#include <PropHuntProtocol.h>

class UDPMovement : public Component{
public:
	UDPComponent* udpComp;
	float speed = 50.0f;

private:

	//Start is called at the start of a scene
	void Start(){

	}

	//Update is called once per frame
	void Update(){
		gameObject->scene->camera = Vector2::Lerp(gameObject->scene->camera, gameObject->position, 2.0f * COUNTER->DeltaTime());
		bool moveu = false;
		if (HF_INPUT->GetButton(hfb_down)){
			gameObject->Translate(0.0f, -speed * COUNTER->DeltaTime());
			moveu = true;
		}
		if (HF_INPUT->GetButton(hfb_up)){
			gameObject->Translate(0.0f, speed * COUNTER->DeltaTime());
			moveu = true;
		}
		if (HF_INPUT->GetButton(hfb_left)){
			gameObject->Translate(-speed * COUNTER->DeltaTime(), 0.0f);
			moveu = true;
		}
		if (HF_INPUT->GetButton(hfb_right)){
			gameObject->Translate(speed * COUNTER->DeltaTime(), 0.0f);
			moveu = true;
		}
		if (moveu){
			Command cmd;
			cmd.commandType = PH_CMD::position;
			cmd.playerID = udpComp->meuID;
			sendto(udpComp->meuSocket, (const char*)&cmd, 50, NULL, (SOCKADDR*)&udpComp->server, sizeof(sockaddr_in));
			
			PositionCommand positionCmd;
			positionCmd.playerID = udpComp->meuID;
			positionCmd.x = gameObject->position.x;
			positionCmd.y = gameObject->position.y;
			sendto(udpComp->meuSocket, (const char*)&positionCmd, 50, NULL, (SOCKADDR*)&udpComp->server, sizeof(sockaddr_in));
		}
	}
};