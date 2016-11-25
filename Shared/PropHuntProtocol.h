#pragma once
#define NUM_PLAYERS 2
#define MSG_TAM 50

enum PH_CMD{
	team,
	position,
	sprite,
	life,
	fire,
	despawn = -1
};

struct Command{
	int playerID;
	int commandType;
};

//tipo de comando 0
struct TeamCommand{//comando para modificar a vida de um player
	int playerID;
	int cmdType;
	int team;//0 para props, 1 para hunters
};

//tipo de comando 1
struct PositionCommand{//comando para setar a posição do player
	int playerID;
	int cmdType;
	float x, y;//as coordenadas para as quais o player deve ser movido
};

//tipo de comando 2
struct SpriteCommand{//comando para trocar a sprite de um player
	int playerID;
	int cmdType;
	int spriteID;
};

//tipo de comando 3
struct LifeCommand{//comando para modificar a vida de um player
	int playerID;
	int cmdType;
	float life;
};

//tipo de comando 4
struct FireCommand{//comando para posicionar um tiro no mapa
	int playerID;
	int cmdType;
	float posX;
	float posY;
	float dirX;
	float dirY;
};

//tipo de comando -1, feito pelo server para despawnar alguns objetos
struct DespawnCommand{//comando para posicionar um tiro no mapa
	int playerID;
	int cmdType;
	int objectID;
};