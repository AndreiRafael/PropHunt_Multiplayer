#pragma once
#include "Component.h"
#include "Vector2.h"
#include "Counter.h"
#include <iostream>


class Rigidbody : public Component{
public:
	Vector2 velocity;
	Vector2 previousPosition;
	bool useGravity = true;
	bool isKinematic = false;

	void Awake(){

	}

	void Start(){
		velocity.x = 0;
		velocity.y = 0;
	}

	void Update(){
		previousPosition = gameObject->position;
		if (useGravity){
			velocity.y -= 9.8f * 2 * COUNTER->DeltaTime();
		}
		gameObject->position = gameObject->position + velocity * COUNTER->DeltaTime() * 10.0f;
	}

	void OnCollisionStay(GameObject* collider){
		Vector2 newVelocity;
		if (!isKinematic){
			newVelocity.x = (gameObject->position.x - collider->position.x) / 10;
			newVelocity.y = (gameObject->position.y - collider->position.y) / 10;
			velocity = newVelocity;
		}
	}
};