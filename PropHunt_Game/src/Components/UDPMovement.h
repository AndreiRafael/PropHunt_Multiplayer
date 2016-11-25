#pragma once
#include <HifireLibrary.h>
#include <PropHuntProtocol.h>
#include "../InputConfig.h"

class UDPMovement : public Component{
public:
	UDPComponent* udpComp;
	BoxCollider* coll;
	Vector2 prevPos;
	float speed = 200.0f;

private:

	//Start is called at the start of a scene
	void Start(){
		coll = GetComponent<BoxCollider>();
		prevPos = gameObject->position;
		SetEnabled(false);
	}

	//Update is called once per frame
	void Update(){
		gameObject->scene->camera = Vector2::Lerp(gameObject->scene->camera, gameObject->position, 2.0f * COUNTER->DeltaTime());
		bool moveu = false;
		if (HF_INPUT->GetButton(hfInput::down)){
			gameObject->Translate(0.0f, -speed * COUNTER->DeltaTime());
			moveu = true;
		}
		if (HF_INPUT->GetButton(hfInput::up)){
			gameObject->Translate(0.0f, speed * COUNTER->DeltaTime());
			moveu = true;
		}
		if (HF_INPUT->GetButton(hfInput::left)){
			gameObject->Translate(-speed * COUNTER->DeltaTime(), 0.0f);
			moveu = true;
		}
		if (HF_INPUT->GetButton(hfInput::right)){
			gameObject->Translate(speed * COUNTER->DeltaTime(), 0.0f);
			moveu = true;
		}
		if (moveu){
			//checagem de colisão
			coll->CheckCollision();
			if (coll->InCollision()){
				gameObject->position = prevPos;
			}
			else
				prevPos = gameObject->position;
			if (gameObject->position.x > 1190.0f)
				gameObject->position.x = 1190.0f;
			if (gameObject->position.x < -1190.0f)
				gameObject->position.x = -1190.0f;
			//mandar para o server
			/*Command cmd;
			cmd.commandType = PH_CMD::position;
			cmd.playerID = udpComp->meuID;
			sendto(udpComp->meuSocket, (const char*)&cmd, 50, NULL, (SOCKADDR*)&udpComp->server, sizeof(sockaddr_in));
			*/
			PositionCommand positionCmd;
			positionCmd.playerID = udpComp->meuID;
			positionCmd.cmdType = PH_CMD::position;
			positionCmd.x = gameObject->position.x;
			positionCmd.y = gameObject->position.y;
			sendto(udpComp->meuSocket, (const char*)&positionCmd, 50, NULL, (SOCKADDR*)&udpComp->server, sizeof(sockaddr_in));
		}
	}
};