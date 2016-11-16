#pragma once
#include <HifireLibrary.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <PropHuntProtocol.h>

class UDPComponent : public Component{
public:
	SOCKET meuSocket;
	sockaddr_in server;
	int tamanhoServer;

	int meuID = -1;//o ID do cliente
private:
	int r;
	int request = 321;//o comando de conex�o
	//configura toda a rede
	void ConfigurarRede(){
		WSAData wsaData;

		r = WSAStartup(MAKEWORD(2, 2), &wsaData);
		meuSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		std::string serverAd;
		//r = bind(meuSocket, (SOCKADDR*)&server, sizeof(sockaddr_in));
		std::cout << "Digite o numero do servidor: ";
		std::cin >> serverAd;
		int porta;

		server.sin_family = AF_INET;
		server.sin_port = htons(9999);
		InetPton(AF_INET, serverAd.c_str(), &server.sin_addr.s_addr);

		tamanhoServer = sizeof(server);

		
	}
	//Start is called at the start of a scene
	void Start(){
		ConfigurarRede();
	}

	//Update is called once per frame
	void Update(){
		
		char buffer[MSG_TAM];
		if (meuID < 0){
			std::cout << "Tentando Conectar...";
			int request = 321;
			sendto(meuSocket, (const char*)&request, 50, NULL, (SOCKADDR*)&server, sizeof(sockaddr_in));
			r = recv(meuSocket, (char*)&buffer, MSG_TAM, NULL);
			if (r != SOCKET_ERROR){
				meuID = *((int*)buffer);
				u_long iMode = 1;
				ioctlsocket(meuSocket, FIONBIO, &iMode);
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
					r = recv(meuSocket, (char*)&buffer, 50, NULL);
					TeamCommand teamMsg;
					if (r != SOCKET_ERROR){
						teamMsg = *((TeamCommand*)buffer);
						//fazer algo
					}
					break;
				case PH_CMD::position:
					r = recv(meuSocket, (char*)&buffer, 50, NULL);
					PositionCommand positionMsg;
					if (r != SOCKET_ERROR){
						positionMsg = *((PositionCommand*)buffer);
						std::cout << "Recebi uma posicao: (" << positionMsg.x << ", " << positionMsg.y << ")" << std::endl;
						//fazer algo
					}
					break;
				case PH_CMD::sprite:
					r = recv(meuSocket, (char*)&buffer, 50, NULL);
					SpriteCommand spriteMsg;
					if (r != SOCKET_ERROR){
						spriteMsg = *((SpriteCommand*)buffer);
						//fazer algo
					}
					break;
				case PH_CMD::life:
					r = recv(meuSocket, (char*)&buffer, 50, NULL);
					LifeCommand lifeMsg;
					if (r != SOCKET_ERROR){
						lifeMsg = *((LifeCommand*)buffer);
						//fazer algo
					}
					break;
				}
			}
		}
	}
};