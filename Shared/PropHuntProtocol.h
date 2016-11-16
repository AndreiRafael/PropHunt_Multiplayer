#pragma once
#define NUM_PLAYERS 2
#define MSG_TAM 50

enum PH_CMD{
	team,
	position,
	sprite,
	life
};

struct Command{
	int playerID;
	int commandType;
};

//tipo de comando 0
struct TeamCommand{//comando para modificar a vida de um player
	int playerID;
	int team;//0 para props, 1 para hunters
};

//tipo de comando 1
struct PositionCommand{//comando para setar a posição do player
	int playerID;
	float x, y;//as coordenadas para as quais o player deve ser movido
};

//tipo de comando 2
struct SpriteCommand{//comando para trocar a sprite de um player
	int playerID;
	int spriteID;
};

//tipo de comando 3
struct LifeCommand{//comando para modificar a vida de um player
	int playerID;
	float life;
};

