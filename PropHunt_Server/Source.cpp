#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <PropHuntProtocol.h>

#include <thread>

SOCKET serverSocket;


class Player{
public:
	bool connected;//esse slot já está tomado?
	sockaddr_in address;//o endereço e infos do cara
};

Player players[NUM_PLAYERS];//o array de players
//funçoes relacionadas ao player

//retorna um ID para ser usado pelo player, -1 se não houver mais espaço
int GetNewID(){
	for (int i = 0; i < NUM_PLAYERS; i++){
		if (!players[i].connected)
			return i;
	}
	return -1;
}

bool IsNewPlayer(sockaddr_in cliente){
	for (int i = 0; i < GetNewID(); i++){
		
	}
}

//conecta o player nesse servidor
void ConnectPlayer(sockaddr_in cliente){
	int id = GetNewID();
	if (id >= 0){//caso o jogo não esteja cheio
		players[id].address = cliente;
		int r;
		r = sendto(serverSocket, (const char*)&id, MSG_TAM, NULL, (SOCKADDR*)&players[id].address, sizeof(players[id].address));
		if (r != SOCKET_ERROR)//se não deu erro na mensagem, conectou
			players[id].connected = true;
		std::cout << "Player " << id << " conectou." << std::endl;
	}
}

//funções para o server

//Retorna true se todos jogadores conectaram
bool GameFull(){
	return GetNewID() == -1;
}

//configura toda a rede
void ConfigurarRede(){
	int r;
	WSAData wsaData;
	r = WSAStartup(MAKEWORD(2, 2), &wsaData);
	serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//tipo: UDP
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(9999);
	InetPton(AF_INET, "0.0.0.0", &serverAddress.sin_addr.s_addr);
	r = bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(sockaddr_in));

	
}

int main(){
	ConfigurarRede();
	while (!GameFull()){
		char buffer[MSG_TAM];
		sockaddr_in novoCliente;
		int tam = sizeof(novoCliente);//tamanho

		int r;
		r = recvfrom(serverSocket, buffer, MSG_TAM, NULL, (SOCKADDR*)&novoCliente, &tam);
		if (r != SOCKET_ERROR){//deu certo
			int request = *((int*)buffer);
			if (request == 321)
				ConnectPlayer(novoCliente);
		}
		else{
			system("cls");
			std::cout << "Aguardando conexao..." << std::endl;
		}
	}
	u_long iMode = 1;
	ioctlsocket(serverSocket, FIONBIO, &iMode);
	while (true){
		std::cout << "Jogo em andamento" << std::endl;
		char buffer[MSG_TAM];

		int r;
		r = recv(serverSocket, buffer, MSG_TAM, NULL);
		if (r != SOCKET_ERROR){
			Command msg = *((Command*)buffer);
			TeamCommand teamMsg;
			PositionCommand positionMsg;
			SpriteCommand spriteMsg;
			LifeCommand lifeMsg;

			switch (msg.commandType){
			case PH_CMD::team:
				r = recv(serverSocket, (char*)&buffer, 50, NULL);
				if (r != SOCKET_ERROR){
					teamMsg = *((TeamCommand*)buffer);
				}
				break;
			case PH_CMD::position:
				r = recv(serverSocket, (char*)&buffer, 50, NULL);
				if (r != SOCKET_ERROR){
					positionMsg = *((PositionCommand*)buffer);
					std::cout << "Recebi uma posicao: (" << positionMsg.x << ", " << positionMsg.y << ")" << std::endl;
				}
				break;
			case PH_CMD::sprite:
				r = recv(serverSocket, (char*)&buffer, 50, NULL);
				if (r != SOCKET_ERROR){
					spriteMsg = *((SpriteCommand*)buffer);
				}
				break;
			case PH_CMD::life:
				r = recv(serverSocket, (char*)&buffer, 50, NULL);
				if (r != SOCKET_ERROR){
					lifeMsg = *((LifeCommand*)buffer);
				}
				break;
			}
			for (int i = 0; i < NUM_PLAYERS; i++){//manda os comandos para os outros players
				if (i != msg.playerID){
					r = sendto(serverSocket, (const char*)&msg, MSG_TAM, NULL, (SOCKADDR*)&players[i].address, sizeof(players[i].address));
					switch (msg.commandType){
					case PH_CMD::team:
						r = sendto(serverSocket, (const char*)&teamMsg, MSG_TAM, NULL, (SOCKADDR*)&players[i].address, sizeof(players[i].address));
						break;
					case PH_CMD::position:
						r = sendto(serverSocket, (const char*)&positionMsg, MSG_TAM, NULL, (SOCKADDR*)&players[i].address, sizeof(players[i].address));
						break;
					case PH_CMD::sprite:
						r = sendto(serverSocket, (const char*)&spriteMsg, MSG_TAM, NULL, (SOCKADDR*)&players[i].address, sizeof(players[i].address));
						break;
					case PH_CMD::life:
						r = sendto(serverSocket, (const char*)&lifeMsg, MSG_TAM, NULL, (SOCKADDR*)&players[i].address, sizeof(players[i].address));
						break;
					}
				}
			}//fim do for
		}
	}

	return 0;
}