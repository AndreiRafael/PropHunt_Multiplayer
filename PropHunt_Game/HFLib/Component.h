#pragma once
#include "GameObject.h"

class Component {
public:
	//the gameObject to wich this component is attached
	GameObject* gameObject;
	//Awake is Called When the component is Added to the GameObject
	virtual void Awake(){};
	//Start is called at the start of the scene
	virtual void Start() {};
	//update is called once per frame
	virtual void Update(){}
	//Function called after Update, usually to render things
	virtual void Render(){}
	//sets if the component is or is not enabled
	void SetEnabled(bool state) {
		enabled = state;
	}
	//returns true if the Component is enabled
	bool isEnabled() {
		return enabled;
	}
	//called when all the gameObject's components are cleared
	virtual void OnDestroy() {

	}
	
protected:
	template<class T>
	T* GetComponent(){
		return gameObject->GetComponent<T>();
	}

private:
	bool enabled = true;
};