#include "GameObject.h"
#include "SceneManager.h"
#include "Component.h"
#include "Renderer.h"
#include "BoxCollider.h"

GameObject::GameObject(SceneManager* p_scene, float p_x, float p_y, int p_layer)
{
	layer = p_layer;
	scene = p_scene;
	scene->AddObject(this);
	objects = scene->gameObjects;
	myNode = objects->at(layer)->m_tail;
	

	position.x = p_x;
	position.y = p_y;
	scale.x = scale.y = 1;
}

GameObject::GameObject(SceneManager* p_scene, float p_x, float p_y) : GameObject(p_scene, 0.0f, 0.0f, 0){}

GameObject::GameObject(SceneManager* p_scene) : GameObject(p_scene, 0.0f, 0.0f) {}

GameObject::GameObject(float p_x, float p_y) : GameObject(GAME_MANAGER->GetLoadedScene(), p_x, p_y){}

GameObject::GameObject(float p_x, float p_y, int layer) : GameObject(GAME_MANAGER->GetLoadedScene(), p_x, p_y, layer){}

GameObject::GameObject() : GameObject(GAME_MANAGER->GetLoadedScene()){}

GameObject::~GameObject(){}

void GameObject::Translate(float p_x, float p_y){
	position.x += p_x;
	position.y += p_y;
}

void GameObject::Translate(Vector2 moveVector){
	position.x += moveVector.x;
	position.y += moveVector.y;
}

void GameObject::SetPosition(Vector2 position){
	this->position = position;
}

void GameObject::SetPosition(float p_x, float p_y){
	this->position.x = p_x;
	this->position.y = p_y;
}

void GameObject::Scale(float p_x, float p_y){
	scale.x *= p_x;
	scale.y *= p_y;
}

void GameObject::Scale(Vector2 scaleVector){
	scale.x *= scaleVector.x;
	scale.y *= scaleVector.y;
}

void GameObject::SetScale(float p_x, float p_y){
	scale.x = p_x;
	scale.y = p_y;
	if (collider != nullptr)
		collider->UpdateSize();
}

void GameObject::SetScale(Vector2 scale){
	this->scale = scale;
	if (collider != nullptr)
		collider->UpdateSize();
}

void GameObject::Start(){
	SetRenderer();
	for (int i = 0; i < componentCount; i++){
		components[i]->Start();
	}
}

void GameObject::Update(){
	if (active){
		for (int i = 0; i < componentCount; i++){
			if(components[i]->isEnabled())
				components[i]->Update();
		}
	}
}

void GameObject::Render(){
	if (active){
		for (int i = 0; i < componentCount; i++){
			if (components[i]->isEnabled())
				components[i]->Render();
		}
	}
}

BoxCollider* GameObject::GetCollider(){
	return collider;
}

void GameObject::SetCollider(BoxCollider* collider){
	this->collider = collider;
}

Renderer* GameObject::GetRenderer(){
	SetRenderer();
	return renderer;
}

void GameObject::SetRenderer(){
	for (int i = 0; i < componentCount; i++){
		if (dynamic_cast<Renderer*>(components[i]) != 0){
			renderer = dynamic_cast<Renderer*>(components[i]);
		}
	}
}

void GameObject::ClearComponents(){
	for (int i = 0; i < componentCount; i++){
		components[i]->OnDestroy();
		delete[] components[i];
	}
	delete[] components;
	componentCount = 0;
}