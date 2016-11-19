#pragma once
#include <HifireLibrary.h>
#include <UDPComponent.h>
#include <UDPMovement.h>
#include <rafael.h>

class SC_Gameplay : public SceneManager{
public:
	void ConfigureObjects();
	void OnSceneEnd();
private:
	GameObject* cenario;
	GameObject** hunters;
	GameObject* prop1;
	GameObject* prop2;
	GameObject* udpReceiver;
	Animation *anim;
};

void SC_Gameplay::ConfigureObjects(){
	GAME_MANAGER->SetBackgroundColor(200, 200, 200);
	SetLayers(1);
	//criação dos objetos
	cenario = new GameObject();
	udpReceiver = new GameObject();
	hunters = new GameObject*[NUM_PLAYERS];
	//adição dos componentes
	udpReceiver->AddComponent<UDPComponent>();
	for (int i = 0; i < NUM_PLAYERS; i++){
		hunters[i] = new GameObject();
		hunters[i]->AddComponent<UDPMovement>();
		hunters[i]->AddComponent<Renderer>();
	}

	cenario->AddComponent<Renderer>();
	//inicialização de componentes
	cenario->GetComponent<Renderer>()->SetTexture("sprintes/level.png");
	for (int i = 0; i < NUM_PLAYERS; i++){
		hunters[i]->GetComponent<UDPMovement>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
		hunters[i]->GetComponent<Renderer>()->SetTexture("sprintes/prop_gnomo-jardim.png");
	}
	udpReceiver->GetComponent<UDPComponent>()->gameObjects = hunters;
}

void SC_Gameplay::OnSceneEnd(){

}