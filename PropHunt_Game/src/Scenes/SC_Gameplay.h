#pragma once
#include <HifireLibrary.h>
#include <UDPComponent.h>
#include <UDPMovement.h>

class SC_Gameplay : public SceneManager{
public:
	void ConfigureObjects();
	void OnSceneEnd();
private:
	GameObject* hunter1;
	GameObject* hunter2;
	GameObject* prop1;
	GameObject* prop2;
	GameObject* udpReceiver;
	Animation *anim;
};

void SC_Gameplay::ConfigureObjects(){
	GAME_MANAGER->SetBackgroundColor(200, 200, 200);
	SetLayers(1);
	//cria��o dos objetos
	udpReceiver = new GameObject();
	hunter1 = new GameObject();
	//adi��o dos componentes
	udpReceiver->AddComponent<UDPComponent>();
	hunter1->AddComponent<UDPMovement>();
	//inicializa��o de componentes
	hunter1->GetComponent<UDPMovement>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
}

void SC_Gameplay::OnSceneEnd(){

}