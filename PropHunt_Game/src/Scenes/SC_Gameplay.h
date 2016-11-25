#pragma once
#include <HifireLibrary.h>
#include <UDPComponent.h>
#include <UDPMovement.h>
#include <LifeManager.h>
#include <rafael.h>
#include <DynamicTexture.h>
#include <TextureManager.h>
#include <TeamSelect.h>
#include <Cursor.h>
#include <VictoryCheck.h>

class SC_Gameplay : public SceneManager{
public:
	void ConfigureObjects();
	void OnSceneEnd();
private:
	GameObject* hudVida;
	GameObject* vitoria;
	GameObject* cenarioFundo;
	GameObject** cenarioColisao;
	GameObject** cenarioMoveis;
	GameObject** hunters;
	GameObject** props;
	GameObject** bullets;
	GameObject* teamSelect;
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

	//adição dos componentes


	cenarioColisao = new GameObject*[14];
	cenarioMoveis = new GameObject*[18];

	cenarioFundo->AddComponent<Renderer>();

	for (int i = 0; i < 14; i++){
		cenarioColisao[i] = new GameObject();
		cenarioColisao[i]->group = 1;
		cenarioColisao[i]->AddComponent<Renderer>();
		cenarioColisao[i]->AddComponent<BoxCollider>();
	}

	for (int i = 0; i < 18; i++){
		cenarioMoveis[i] = new GameObject();
		cenarioMoveis[i]->group = 1;
		cenarioMoveis[i]->AddComponent<Renderer>();
		cenarioMoveis[i]->AddComponent<BoxCollider>();
	}

	hunters = new GameObject*[NUM_PLAYERS];
	props = new GameObject*[NUM_PLAYERS];
	for (int i = 0; i < NUM_PLAYERS; i++){
		hunters[i] = new GameObject();
		hunters[i]->group = 3;
		hunters[i]->AddComponent<UDPMovement>();
		hunters[i]->AddComponent<UDPWeapon>();
		hunters[i]->AddComponent<LifeManager>();
		hunters[i]->AddComponent<Renderer>();
		hunters[i]->AddComponent<BoxCollider>();
		hunters[i]->GetComponent<LifeManager>()->life = 20.0f;
		hunters[i]->SetPosition(i * 60, -60);
		hunters[i]->SetActive(false);

		props[i] = new GameObject();
		props[i]->group = 2;
		props[i]->AddComponent<UDPMovement>();
		props[i]->AddComponent<DynamicTexture>();
		props[i]->AddComponent<LifeManager>();
		//por componente de dano bala
		props[i]->AddComponent<Renderer>();
		props[i]->AddComponent<BoxCollider>();
		props[i]->GetComponent<LifeManager>()->life = 5.0f;
		props[i]->SetPosition(i * 50 - 600, 0);
		props[i]->SetActive(false);
	}

	bullets = new GameObject*[NUM_PLAYERS * 10];
	for (int i = 0; i < NUM_PLAYERS * 10; i++){
		bullets[i] = new GameObject();
		bullets[i]->SetActive(false);

		bullets[i]->AddComponent<Renderer>();
		bullets[i]->AddComponent<BoxCollider>();
		bullets[i]->AddComponent<Bullet>();
	}

	hudVida = new GameObject(-340.0f, -280.0f);
	//hudVida->SetPosition(-250.0f, -280.0f);
	hudVida->AddComponent<HudText>();
	hudVida->GetComponent<HudText>()->SetFont("fonte.ttf", 32);
	hudVida->GetComponent<HudText>()->SetText("HP:");

	udpReceiver = new GameObject();
	udpReceiver->AddComponent<UDPComponent>();
	udpReceiver->AddComponent<HudRenderer>();


	teamSelect = new GameObject();
	teamSelect->AddComponent<TeamSelect>();
	teamSelect->AddComponent<HudRenderer>();

	vitoria = new GameObject();
	vitoria->SetActive(false);
	vitoria->AddComponent<HudRenderer>();
	vitoria->AddComponent<VictoryCheck>();

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
	cenarioColisao[13]->GetComponent<Renderer>()->SetTexture("sprintes/cenario/mapaCercaInferior.png");//cerca
	cenarioColisao[13]->GetComponent<BoxCollider>()->FitSprite();

	//cenario moveis ----------------
	cenarioMoveis[0]->SetPosition(925, 494);//pia banheiro
	cenarioMoveis[0]->GetComponent<Renderer>()->SetTexture("sprintes/prop_pia.png");//cerca
	cenarioMoveis[0]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[0]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[0]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[0]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[0]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[0]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[1]->SetPosition(1058, 494);//vaso sanitario
	cenarioMoveis[1]->GetComponent<Renderer>()->SetTexture("sprintes/prop_vaso-sanitario.png");//cerca
	cenarioMoveis[1]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[1]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[1]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[1]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[1]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[1]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[2]->SetPosition(1064, 278);//lixeira banheiro
	cenarioMoveis[2]->GetComponent<Renderer>()->SetTexture("sprintes/prop_cesto-de-lixo.png");//cerca
	cenarioMoveis[2]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[2]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[2]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[2]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[2]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[2]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[3]->SetPosition(72, 477);//cama
	cenarioMoveis[3]->GetComponent<Renderer>()->SetTexture("sprintes/prop_cama.png");//cerca
	cenarioMoveis[3]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[3]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[3]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[3]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[3]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[3]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[4]->SetPosition(253, 499);//comoda
	cenarioMoveis[4]->GetComponent<Renderer>()->SetTexture("sprintes/prop_comoda.png");//cerca
	cenarioMoveis[4]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[4]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[4]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[4]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[4]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[4]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[5]->SetPosition(369, 177);//fogão
	cenarioMoveis[5]->GetComponent<Renderer>()->SetTexture("sprintes/prop_fogao.png");//cerca
	cenarioMoveis[5]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[5]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[5]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[5]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[5]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[5]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[6]->SetPosition(-27, 192);//geladeira
	cenarioMoveis[6]->GetComponent<Renderer>()->SetTexture("sprintes/prop_geladeira.png");//cerca
	cenarioMoveis[6]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[6]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[6]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[6]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[6]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[6]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[7]->SetPosition(124, 94);//cadeira frente
	cenarioMoveis[7]->GetComponent<Renderer>()->SetTexture("sprintes/prop_cadeira-frente.png");//cerca
	cenarioMoveis[7]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[7]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[7]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[7]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[7]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[7]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[8]->SetPosition(130, -112);//cadeira-tras
	cenarioMoveis[8]->GetComponent<Renderer>()->SetTexture("sprintes/prop_cadeira-tras.png");//cerca
	cenarioMoveis[8]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[8]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[8]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[8]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[8]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[8]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[9]->SetPosition(235, -112);//cadeira-tras2
	cenarioMoveis[9]->GetComponent<Renderer>()->SetTexture("sprintes/prop_cadeira-tras.png");//cerca
	cenarioMoveis[9]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[9]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[9]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[9]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[9]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[9]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[10]->SetPosition(1085, 168);//TV
	cenarioMoveis[10]->GetComponent<Renderer>()->SetTexture("sprintes/prop_TV.png");//cerca
	cenarioMoveis[10]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[10]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[10]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[10]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[10]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[10]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[11]->SetPosition(898, 163);//sofa
	cenarioMoveis[11]->GetComponent<Renderer>()->SetTexture("sprintes/prop_sofa.png");//cerca
	cenarioMoveis[11]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[11]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[11]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[11]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[11]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[11]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[12]->SetPosition(970, -33);//tapete
	cenarioMoveis[12]->GetComponent<Renderer>()->SetTexture("sprintes/prop_tapete.png");//cerca
	cenarioMoveis[12]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[12]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[12]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[12]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[12]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[12]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[13]->SetPosition(1071, -110);//controle
	cenarioMoveis[13]->GetComponent<Renderer>()->SetTexture("sprintes/prop_controle-remoto.png");//cerca
	cenarioMoveis[13]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[13]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[13]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[13]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[13]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[13]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[14]->SetPosition(-177, 167);//vaso flor 1
	cenarioMoveis[14]->GetComponent<Renderer>()->SetTexture("sprintes/prop_vaso-de-flor.png");//cerca
	cenarioMoveis[14]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[14]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[14]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[14]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[14]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[14]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[15]->SetPosition(-177, -110);//vaso2
	cenarioMoveis[15]->GetComponent<Renderer>()->SetTexture("sprintes/prop_vaso-de-flor.png");//cerca
	cenarioMoveis[15]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[15]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[15]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[15]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[15]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[15]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[16]->SetPosition(-177, -185);//vaso3
	cenarioMoveis[16]->GetComponent<Renderer>()->SetTexture("sprintes/prop_vaso-de-flor.png");//cerca
	cenarioMoveis[16]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[16]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[16]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[16]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[16]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[16]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	cenarioMoveis[17]->SetPosition(184, 18);//mesa
	cenarioMoveis[17]->GetComponent<Renderer>()->SetTexture("sprintes/prop_mesa.png");//cerca
	cenarioMoveis[17]->GetComponent<BoxCollider>()->FitSprite();
	cenarioMoveis[17]->GetComponent<BoxCollider>()->SetCollisionRectSize(cenarioMoveis[17]->GetComponent<BoxCollider>()->GetCollisionWidth()
		, cenarioMoveis[17]->GetComponent<BoxCollider>()->GetCollisionHeight() / 2);
	cenarioMoveis[17]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -cenarioMoveis[17]->GetComponent<BoxCollider>()->GetCollisionHeight() * 0.5f);

	for (int i = 0; i < NUM_PLAYERS; i++){
		props[i]->GetComponent<UDPMovement>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
		props[i]->GetComponent<DynamicTexture>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
		props[i]->GetComponent<LifeManager>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
		props[i]->GetComponent<Renderer>()->SetTexture("sprintes/prop_gnomo-jardim.png");
		props[i]->GetComponent<BoxCollider>()->FitSprite();

		hunters[i]->GetComponent<UDPMovement>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
		hunters[i]->GetComponent<LifeManager>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
		hunters[i]->GetComponent<Renderer>()->SetTexture("sprintes/hunter.png");
		hunters[i]->GetComponent<Renderer>()->DivideTiles(3, 4);
		hunters[i]->GetComponent<BoxCollider>()->FitSprite();
		hunters[i]->GetComponent<BoxCollider>()->SetCollisionRectSize(hunters[i]->GetComponent<BoxCollider>()->GetCollisionWidth() * 0.9f
																	, hunters[i]->GetComponent<BoxCollider>()->GetCollisionHeight()/6);
		hunters[i]->GetComponent<BoxCollider>()->SetCollisionOffset(0.0f, -hunters[i]->GetComponent<BoxCollider>()->GetCollisionHeight() * 2.5f);
		hunters[i]->GetComponent<UDPWeapon>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
	}

	for (int i = 0; i < NUM_PLAYERS * 10; i++){
		bullets[i]->GetComponent<Renderer>()->SetTexture("sprintes/bullet.png");
		bullets[i]->GetComponent<BoxCollider>()->FitSprite();
	}

	teamSelect->GetComponent<TeamSelect>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
	teamSelect->GetComponent<HudRenderer>()->SetTexture("sprintes/apres/two.png");
	teamSelect->GetComponent<TeamSelect>()->hud = hudVida;
	teamSelect->GetComponent<TeamSelect>()->victCheck = vitoria;

	vitoria->GetComponent<VictoryCheck>()->udpComp = udpReceiver->GetComponent<UDPComponent>();
	vitoria->GetComponent<HudRenderer>()->SetTexture("sprintes/apres/huntWin.png");

	udpReceiver->GetComponent<HudRenderer>()->SetTexture("sprintes/apres/one.png");
	udpReceiver->GetComponent<UDPComponent>()->hunterArray = hunters;
	udpReceiver->GetComponent<UDPComponent>()->propArray = props;
	udpReceiver->GetComponent<UDPComponent>()->teamSelect = teamSelect;
	udpReceiver->GetComponent<UDPComponent>()->bullets = bullets;
	udpReceiver->GetComponent<UDPComponent>()->moveis = cenarioMoveis;
}

void SC_Gameplay::OnSceneEnd(){

}