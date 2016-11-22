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

	cenarioColisao = new GameObject*[14];

	cenarioFundo->AddComponent<Renderer>();

	for (int i = 0; i < 14; i++){
		cenarioColisao[i] = new GameObject();
		cenarioColisao[i]->group = 1;
		cenarioColisao[i]->AddComponent<Renderer>();
		cenarioColisao[i]->AddComponent<BoxCollider>();
	}

	for (int i = 0; i < NUM_PLAYERS; i++){
		hunters[i] = new GameObject();
		hunters[i]->AddComponent<UDPMovement>();
		hunters[i]->AddComponent<DynamicTexture>();
		hunters[i]->AddComponent<Renderer>();
		hunters[i]->AddComponent<BoxCollider>();
		hunters[i]->SetPosition(i * 50, 0);
	}

	//inicialização de componentes
	cenarioFundo->GetComponent<Renderer>()->SetTexture("sprintes/cenario/mapaBase.png");

	cenarioColisao[0]->SetPosition(-699, 565);//cerca top
	cenarioColisao[0]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/mapaCercaSuperior.png");//cerca
	cenarioColisao[0]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[1]->SetPosition(-116, 360);//parede esquerda
	cenarioColisao[1]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-esquerda.png");//cerca
	cenarioColisao[1]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[2]->SetPosition(-116, -149);//parede esquerda 2
	cenarioColisao[2]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-esquerda-2.png");//cerca
	cenarioColisao[2]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[3]->SetPosition(557, 557);//parede cima
	cenarioColisao[3]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-cima.png");//cerca
	cenarioColisao[3]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[4]->SetPosition(1167, 157);//parede direta
	cenarioColisao[4]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-direita.png");//cerca
	cenarioColisao[4]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[5]->SetPosition(526, -184);//parede baixo
	cenarioColisao[5]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-baixo.png");//cerca
	cenarioColisao[5]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[6]->SetPosition(455, 434);//parede quarto 2
	cenarioColisao[6]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-quarto-2.png");//cerca
	cenarioColisao[6]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[7]->SetPosition(197, 223);//parede quarto
	cenarioColisao[7]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-quarto.png");//cerca
	cenarioColisao[7]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[8]->SetPosition(456, -92);//parede cozinha
	cenarioColisao[8]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-cozinha.png");//cerca
	cenarioColisao[8]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[9]->SetPosition(456, 156);//parede cozinha2
	cenarioColisao[9]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-cozinha-2.png");//cerca
	cenarioColisao[9]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[10]->SetPosition(813, 468);//parede banheiro 1
	cenarioColisao[10]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-banheiro-1.png");//cerca
	cenarioColisao[10]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[11]->SetPosition(813, 255);//parede banheiro 2
	cenarioColisao[11]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-banheiro-2.png");//cerca
	cenarioColisao[11]->GetComponent<BoxCollider>()->FitSprite();

	cenarioColisao[12]->SetPosition(964, 233);//parede banheiro 3
	cenarioColisao[12]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/parede-banheiro-3.png");//cerca
	cenarioColisao[12]->GetComponent<BoxCollider>()->FitSprite();
		
	cenarioColisao[13]->SetPosition(0, -564);//cerca inferior
	cenarioColisao[13]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/mapaCercaSuperior.png");//cerca
	cenarioColisao[13]->GetComponent<BoxCollider>()->FitSprite();

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