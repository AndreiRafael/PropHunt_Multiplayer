#include "SceneManager.h"
#include "TextureManager.h"


SceneManager::SceneManager()
{
	layers = nullptr;
	camera.x = 0;
	camera.y = 0;
}

SceneManager::~SceneManager()
{
}


void SceneManager::End()
{
	for (int j = 0; j < gameObjects->size(); j++) {
		for (DoubleNode<GameObject*>* i = gameObjects->at(j)->m_head; i != nullptr; i = i->m_nextNode) {
			i->m_data->ClearComponents();// ClearComponents();
		}
	}
	for (int i = 0; i < gameObjects->size(); i++) {
		while (gameObjects->at(i)->m_head != nullptr) {
			gameObjects->at(i)->DeleteHead();
		}
		delete gameObjects->at(i);
	}
	delete gameObjects;
	
	TEXTURES->ClearTextures();
	OnSceneEnd();
}

void SceneManager::SetLayers(int count)
{
	if (count > 0) {
		gameObjects = new std::vector<DoubleNodeList<GameObject*>*>(count);
		for (int i = 0; i < count; i++) {
			gameObjects->at(i) = new DoubleNodeList<GameObject*>;
		}
	}
}

void SceneManager::AddObject(GameObject* object) {
	if(object->layer < gameObjects->size())
		gameObjects->at(object->layer)->Append(object);
}

DoubleNodeList<GameObject*>* SceneManager::GetGameObjects(int layer) {
	return gameObjects->at(layer);
}

int SceneManager::GetLayerCount(){
	return gameObjects->size();
}

void SceneManager::Start() {
	ConfigureObjects();
	for (int j = 0; j < gameObjects->size(); j++) {
		DoubleNode<GameObject*>* curr = gameObjects->at(j)->m_head;
		for (int i = 0; i < gameObjects->at(j)->m_count; i++) {
			curr->m_data->Start();
			curr = curr->m_nextNode;
		}
	}
}

void SceneManager::Update() {
	for (int j = 0; j < gameObjects->size(); j++) {
		DoubleNode<GameObject*>* curr = gameObjects->at(j)->m_head;
		for (int i = 0; i < gameObjects->at(j)->m_count; i++) {
			if (curr != nullptr) {
				DoubleNode<GameObject*>* now = curr;
				curr = curr->m_nextNode;
				if (now != nullptr)
					if (now->m_data != nullptr)
						now->m_data->Update();
			}
		}
	}
	for (int j = 0; j < gameObjects->size(); j++) {
		DoubleNode<GameObject*>* curr = gameObjects->at(j)->m_head;
		for (int i = 0; i < gameObjects->at(j)->m_count; i++) {
			if (curr != nullptr) {
				DoubleNode<GameObject*>* now = curr;
				curr = curr->m_nextNode;
				if (now != nullptr && now->m_data != nullptr)
					now->m_data->Render();
			}
		}
	}
}