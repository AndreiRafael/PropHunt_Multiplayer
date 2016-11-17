#pragma once
#include <HifireLibrary.h>

class Cursor : public Component{
private:

public:
	//Start is called at the start of the scene
	void Start(){
		
	}

	//update is called once per frame
	void Update(){
		HF_INPUT->GetMousePosition(&gameObject->position);
	}
};