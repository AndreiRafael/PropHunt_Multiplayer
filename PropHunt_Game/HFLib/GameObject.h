#pragma once
#include "Vector2.h"
#include "LinkedLists.h"
#include <iostream>
#include <vector>
//#include "SceneManager.h"

class SceneManager;
class Component;
class Renderer;
class BoxCollider;

/*-GameObject is the base class for every
  other object in the game.
*/
class GameObject
{
	friend class SceneManager;
	friend class Component;

private:
	//layer - defines the order the object will be updated and redered
	int layer = 0;
	//the array wich has all the gameObjects
	std::vector<DoubleNodeList<GameObject*>*>* objects;
	//my node in the listings
	DoubleNode<GameObject*>* myNode;
	//The library components
	Renderer* renderer;
	BoxCollider* collider;
	bool active = true;//is the gameObject active?

public:
	//-the position of the gameObject
	Vector2 position;
	//-the scale of the gameObject
	Vector2 scale;
	//-the rotaton in degrees of the gameObject
	float rotation;
	//-the scene in wich the player is
	SceneManager* scene = nullptr;
	//-the group of the game Object, default is 0
	int group = 0;
	//-returns the layer of the gameObject
	int GetLayer() {
		return layer;
	}

	Vector2 GetPosition(){
		return position;
	}

	Vector2 GetScale(){
		return scale;
	}
	
	GameObject();
	GameObject(SceneManager* scene);
	GameObject(float p_x, float p_y);
	GameObject(float p_x, float p_y, int);
	GameObject(SceneManager* scene, float p_x, float p_y);
	GameObject(SceneManager* scene, float p_x, float p_y, int);
	~GameObject();


	virtual void Start();
	virtual void Update();
	virtual void Render();

	void Translate(float p_x, float p_y);//translates the object
	void Translate(Vector2 moveVector);//translates the object
	void SetPosition(Vector2 position);//sets the position of the object
	void SetPosition(float p_x, float p_y);//sets the position of the object
	void Scale(float p_x, float p_y);//multiply each component of the scale by the floats
	void Scale(Vector2);//multiply each component of the scale by the components of the vector
	void SetScale(float, float);//sets the scale of the object
	void SetScale(Vector2);//sets the scale of the object
	
	template <class T>
	//Returns a gameObject Component
	T* GetComponent(){
		for (int i = 0; i < componentCount; i++){
			if (dynamic_cast<T*>(components[i]) != 0){
				return dynamic_cast<T*>(components[i]);
			}
		}
		return nullptr;
	}

	template <class T>
	//Returns a gameObject Component by its index
	T* GetComponent(int index){
			if (dynamic_cast<T*>(components[index]) != 0)
				return dynamic_cast<T*>(components[index]);
		return nullptr;
	}

	template<class T>
	//Adds a Component to the gameObject
	void AddComponent(){
		T* component = new T;
		componentCount++;
		Component** newArray = new Component*[componentCount];
		for (int i = 0; i < componentCount - 1; i++){
			newArray[i] = components[i];
		}
		delete[] components;
		components = new Component*[componentCount];
		for (int i = 0; i < componentCount - 1; i++){
			components[i] = newArray[i];
		}
		components[componentCount - 1] = component;
		components[componentCount - 1]->gameObject = this;
		components[componentCount - 1]->Awake();
		delete[] newArray;
	}

	int GetComponentCount(){
		return componentCount;
	}

	Component** GetComponents(){
		return components;
	}

	BoxCollider* GetCollider();
	void SetCollider(BoxCollider*);
	Renderer* GetRenderer();
	void SetRenderer();

	void ClearComponents();

	void SetActive(bool set){
		active = set;
	}

	bool IsActive() {
		return active;
	}

	void MoveToLayer(int layerID) {
		if (layerID != layer) {
			objects->at(layer)->Remove(myNode);
			layer = layerID;
			objects->at(layer)->Insert(myNode);
		}
	}


protected:
	//-The Components attached to the game Object
	Component** components;
	int componentCount = 0;
};

