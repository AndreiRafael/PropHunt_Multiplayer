#include <Bullet.h>
#include <LifeManager.h>

void Bullet::Update(){
	gameObject->position += direction * 350.0f * COUNTER->DeltaTime();
	col->CheckCollision();
	if (col->EnteredCollision()){
		GameObject* collided = col->GetCollisionObject();
		if (collided->group != 3){
			gameObject->SetActive(false);
		}
		if (collided->group == 1){
			if (shooter != nullptr)
				shooter->GetComponent<LifeManager>()->TakeDamage(1.0f);
		}
		else if (collided->group == 2){//prop
			collided->GetComponent<LifeManager>()->TakeDamage(1.0f);
			if (shooter != nullptr)
				shooter->GetComponent<LifeManager>()->TakeDamage(-1.0f);
		}
	}
}