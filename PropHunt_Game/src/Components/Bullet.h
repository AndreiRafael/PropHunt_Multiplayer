#pragma once
#include <HifireLibrary.h>

class Bullet : public Component{
public:
	Vector2 direction;
	BoxCollider* col;
	GameObject* shooter;
	int hunterID = 0;

private:
	//Start is called at the start of a scene
	void Start(){
		col = GetComponent<BoxCollider>();
	}

	//Update is called once per frame
	void Update();
};