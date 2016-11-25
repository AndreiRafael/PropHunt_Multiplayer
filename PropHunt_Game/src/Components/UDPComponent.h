#pragma once
#include <HifireLibrary.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <PropHuntProtocol.h>
#include <thread>
#include <Bullet.h>

class UDPComponent : public Component{
public:
	SOCKET meuSocket;
	sockaddr_in server;
	int tamanhoServer;
	GameObject** propArray;
	GameObject** hunterArray;
	GameObject* teamSelect;
	GameObject* waitingImage;
	GameObject** bullets;
	GameObject** moveis;
	int currBullet = 0;
	int maxBullets = NUM_PLAYERS * 10;
	
	bool gameReady = false;
	float gameStartTimer = 15.0f;

	int meuID = -1;//o ID do cliente
	int myTeam = -1;
private:
	int r;
	int request = 321;//o comando de conexão
	//configura toda a rede
	void ConfigurarRede(){
		WSAData wsaData;

		r = WSAStartup(MAKEWORD(2, 2), &wsaData);
		meuSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		std::string serverAd;
		//r = bind(meuSocket, (SOCKADDR*)&server, sizeof(sockaddr_in));
		//std::cout << "Digite o numero do servidor: ";
		//std::cin >> serverAd;
		int porta;

		server.sin_family = AF_INET;
		server.sin_port = htons(9999);
		//InetPton(AF_INET, serverAd.c_str(), &server.sin_addr.s_addr);
		InetPton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);

		tamanhoServer = sizeof(server);		
	}
	//Start is called at the start of a scene
	void Start(){
		ConfigurarRede();
		std::thread* th = new std::thread(&UDPComponent::ReceberPacotes, this);
	}

	void ReceberPacotes(){
		while (true){
			char buffer[MSG_TAM];
			if (meuID < 0){
				std::cout << "Tentando Conectar...";
				int request = 321;
				sendto(meuSocket, (const char*)&request, 50, NULL, (SOCKADDR*)&server, sizeof(sockaddr_in));
				r = recv(meuSocket, (char*)&buffer, MSG_TAM, NULL);
				if (r != SOCKET_ERROR){
					meuID = *((int*)buffer);
					//u_long iMode = 1;
					//ioctlsocket(meuSocket, FIONBIO, &iMode);
					for (int i = 0; i < NUM_PLAYERS; i++){
						if (i != meuID){
							propArray[i]->GetRawComponent(0)->SetEnabled(false);//desativa o movement
							propArray[i]->GetRawComponent(1)->SetEnabled(false);//desativa a troca de sprite
						}
					}

				}
			}
			else if (!gameReady){
				//receber confirmação de que o jogo já pode começar
				r = recv(meuSocket, (char*)&buffer, MSG_TAM, NULL);
				if (r != SOCKET_ERROR){
					gameReady = *((bool*)buffer);
					if (gameReady){//ativamos o objeto que permite a escolha de times
						teamSelect->SetActive(true);
						std::cout << "Hora de escolher o time" << std::endl;
						GetComponent<HudRenderer>()->SetEnabled(false);
						for (int i = 0; i < NUM_PLAYERS; i++){
							r = recv(meuSocket, (char*)&buffer, MSG_TAM, NULL);
							DespawnCommand despMsg;
							despMsg = *((DespawnCommand*)buffer);
							moveis[despMsg.objectID]->SetActive(false);
						}
					}
				}
			}
			else{
				int r;
				r = recv(meuSocket, (char*)&buffer, 50, NULL);

				Command msg;
				if (r != SOCKET_ERROR){
					msg = *((Command*)buffer);

					switch (msg.commandType){
					case PH_CMD::team:
						//r = recv(meuSocket, (char*)&buffer, 50, NULL);
						TeamCommand teamMsg;
						if (r != SOCKET_ERROR){
							teamMsg = *((TeamCommand*)buffer);
							if (teamMsg.playerID < NUM_PLAYERS && teamMsg.playerID >= 0){
								//fazer algo
								switch (teamMsg.team){
								case 0:
									propArray[teamMsg.playerID]->SetActive(true);
									break;
								case 1:
									hunterArray[teamMsg.playerID]->SetActive(true);
									break;
								}
							}
						}
						break;
					case PH_CMD::position:
						//r = recv(meuSocket, (char*)&buffer, 50, NULL);
						PositionCommand positionMsg;
						if (r != SOCKET_ERROR){
							positionMsg = *((PositionCommand*)buffer);
							if (positionMsg.playerID < NUM_PLAYERS && positionMsg.playerID >= 0){
								propArray[positionMsg.playerID]->position.x = positionMsg.x;
								propArray[positionMsg.playerID]->position.y = positionMsg.y;

								hunterArray[positionMsg.playerID]->position.x = positionMsg.x;
								hunterArray[positionMsg.playerID]->position.y = positionMsg.y;
								//fazer algo
							}
						}
						break;
					case PH_CMD::sprite:
						//r = recv(meuSocket, (char*)&buffer, 50, NULL);
						SpriteCommand spriteMsg;
						if (r != SOCKET_ERROR){
							spriteMsg = *((SpriteCommand*)buffer);
							if (spriteMsg.playerID < NUM_PLAYERS && spriteMsg.playerID >= 0){
								propArray[spriteMsg.playerID]->GetRenderer()->SetTexture(spriteMsg.spriteID);
								BoxCollider* col = propArray[spriteMsg.playerID]->GetCollider();
								col->FitSprite();
								col->SetCollisionRectSize(col->GetCollisionWidth(), col->GetCollisionHeight() / 2);
								col->SetCollisionOffset(0, -col->GetCollisionHeight() / 2.0f);
								//fazer algo
							}
						}
						break;
					case PH_CMD::life:
						//r = recv(meuSocket, (char*)&buffer, 50, NULL);
						LifeCommand lifeMsg;
						if (r != SOCKET_ERROR){
							lifeMsg = *((LifeCommand*)buffer);
							if (lifeMsg.playerID < NUM_PLAYERS && lifeMsg.playerID >= 0){
								//fazer algo
								if (lifeMsg.life <= 0.0f){
									propArray[lifeMsg.playerID]->SetActive(false);
									hunterArray[lifeMsg.playerID]->SetActive(false);
								}
							}
						}
						break;
					case PH_CMD::fire:
						//r = recv(meuSocket, (char*)&buffer, 50, NULL);
						FireCommand fireMsg;
						if (r != SOCKET_ERROR){
							fireMsg = *((FireCommand*)buffer);
							if (fireMsg.playerID < NUM_PLAYERS && fireMsg.playerID >= 0){
								//fazer algo com as bullets
								bullets[currBullet]->SetActive(true);
								bullets[currBullet]->position.x = fireMsg.posX;
								bullets[currBullet]->position.y = fireMsg.posY;
								Vector2 dir(fireMsg.dirX, fireMsg.dirY);
								bullets[currBullet]->GetComponent<Bullet>()->direction = dir;
								currBullet++;
								if (currBullet >= maxBullets)
									currBullet = 0;
							}
						}
						break;
					}
				}
			}
		}
	}

	//Update is called once per frame
	void Update(){
		
		
	}
};