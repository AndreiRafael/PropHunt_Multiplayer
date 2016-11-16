#pragma once
#include "GameObject.h"
#include "LinkedLists.h"
#include <vector>

struct Layer {
	int count = 0;//how many objects are there in this layer
	DoubleNode<GameObject*>* first;//the first node of the layer

	void AddToLayer(DoubleNode<GameObject*>* node) {
		if (count > 0) {
			node->m_nextNode = first;
			node->m_previousNode = first->m_previousNode;
			first->m_previousNode = node;
		}
		else{
			first = node;
		}
		count++;
	}

	void RemoveFromLayer(DoubleNode<GameObject*>* node) {
		if (node == first) {
			if (count > 1) {
				first = node->m_previousNode;
			}
		}
		if(node->m_previousNode !=nullptr)
			node->m_previousNode->m_nextNode = node->m_nextNode;
		if (node->m_nextNode != nullptr)
			node->m_nextNode->m_previousNode = node->m_previousNode;
		count--;
	}
};

class SceneManager
{
	friend class GameObject;
public:
	Vector2 camera;
	SceneManager();
	~SceneManager();
	void AddObject(GameObject* object);
	void Start();
	void Update();
	virtual void ConfigureObjects() = 0;
	void End();
	virtual void OnSceneEnd() = 0;
	void SetLayers(int count);

	int GetLayerCount();
	DoubleNodeList<GameObject*>* GetGameObjects(int);
private:
	std::vector<DoubleNodeList<GameObject*>*>* gameObjects;
	std::vector<Layer>* layers = nullptr;
};

