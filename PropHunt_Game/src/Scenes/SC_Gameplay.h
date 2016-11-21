#pragma once
#include <HifireLibrary.h>
#include <UDPComponent.h>
#include <UDPMovement.h>
#include <rafael.h>
#include <DynamicTexture.h>
#include <TextureManager.h>

class SC_Gameplay : public SceneManager{
public:
	void ConfigureObjects();
	void OnSceneEnd();
private:
	GameObject* cenarioFundo;
	GameObject** cenarioColisao;
	GameObject** hunters;
	GameObject* prop1;
	GameObject* prop2;
	GameObject* udpReceiver;
	Animation *anim;
};

void SC_Gameplay::ConfigureObjects(){
	GAME_MANAGER->SetBackgroundColor(200, 200, 200);
	SetLayers(1);
	//pré-carregamento das sprites dos props
	TEXTURES->AddTexture("Assets/sprintes/prop_arbusto.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_arbusto2.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_arvore.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_cadeira-frente.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_cadeira-tras.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_cama.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_cesto-de-lixo.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_comoda.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_controle-remoto.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_flor.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_fogao.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_geladeira.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_gnomo-jardim.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_mesa.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_pia.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_sofa.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_tapete.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_TV.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_vaso-de-flor.png");
	TEXTURES->AddTexture("Assets/sprintes/prop_vaso-sanitario.png");
	//criação dos objetos
	cenarioFundo = new GameObject();
	udpReceiver = new GameObject();
	hunters = new GameObject*[NUM_PLAYERS];
	//adição dos componentes
	udpReceiver->AddComponent<UDPComponent>();
	for (int i = 0; i < NUM_PLAYERS; i++){
		hunters[i] = new GameObject();
		hunters[i]->AddComponent<UDPMovement>();
		hunters[i]->AddComponent<DynamicTexture>();
		hunters[i]->AddComponent<Renderer>();
		hunters[i]->AddComponent<BoxCollider>();
		hunters[i]->SetPosition(i * 50, 0);
	}

	cenarioFundo->AddComponent<Renderer>();
	//inicialização de componentes
	cenarioFundo->GetComponent<Renderer>()->SetTexture("sprintes/cenario/mapaBase.png");

	cenarioColisao = new GameObject*[1];

	for (int i = 0; i < 1; i++){
		cenarioColisao[i] = new GameObject();
		cenarioColisao[i]->AddComponent<Renderer>();
		cenarioColisao[i]->AddComponent<BoxCollider>();
	}
	cenarioColisao[0]->SetPosition(-699, 565);
	cenarioColisao[0]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/mapaCercaSuperior.png");//cerca
	cenarioColisao[0]->GetComponent<BoxCollider>()->FitSprite();

	for (int i = 0; i < NUM_PLAYERS; i++){
		hunters[i]->GetComponent<UDPMovement>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
		hunters[i]->GetComponent<DynamicTexture>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
		hunters[i]->GetComponent<Renderer>()->SetTexture("sprintes/prop_gnomo-jardim.png");
		hunters[i]->GetComponent<BoxCollider>()->FitSprite();
	}
	udpReceiver->GetComponent<UDPComponent>()->gameObjects = hunters;
}

void SC_Gameplay::OnSceneEnd(){

}