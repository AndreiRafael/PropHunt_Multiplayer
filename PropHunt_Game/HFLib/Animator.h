#pragma once
#include "Component.h"
#include "Counter.h"
#include "Renderer.h"

struct Frame{
	int x, y;
	float duration;
};

class Animation{
public:
	Frame* frames;
	int frameCount = 0;

	//Adds a frame with the duration informed
	void AddFrame(const int p_x, const int p_y, const float p_duration){
		frameCount += 1;
		Frame* newArray = new Frame[frameCount];
		for (int i = 0; i < frameCount - 1; i++)	{
			newArray[i] = frames[i];
		}
		delete[] frames;
		frames = new Frame[frameCount];
		for (int i = 0; i < frameCount - 1; i++)	{
			frames[i] = newArray[i];
		}
		delete[] newArray;
		frames[frameCount - 1].x = p_x;
		frames[frameCount - 1].y = p_y;
		frames[frameCount - 1].duration = p_duration;
	}
	//Adds a frame with duration of 1.0
	void AddFrame(const int p_x, const int p_y){
		AddFrame(p_x, p_y, 1.0f);
	}

	//loads and adds an animation by reading from an external .hfanim file
	static Animation* LoadFromFile(std::string fileName){
		Animation* animation = new Animation;
		FILE* file;
		fopen_s(&file, ("Assets/" + fileName).c_str(), "r");
		int frames;
		fscanf_s(file, "frames:%d\n", &frames);
		for (int i = 0; i < frames; i++){
			int x, y;
			float dur;
			fscanf_s(file, "%d-%d-%f\n", &x, &y, &dur);
			animation->AddFrame(x, y, dur);
			std::cout << x << std::endl
				<< y << std::endl
				<< dur << std::endl << std::endl;
		}
		return animation;
	}
};

class Animator : public Component{
private:
	//the currrent frame of the animation
	int currentFrame = 0;
	//animation array wich can be accessed by the animator
	Animation** animations;
	//the current animation taken from the animations array
	int currentAnimation = -1;
	//the count of animations
	int animationCount = 0;
	//the speed in wich the animation will be played
	float speed = 1.0f;
	//timer for frame calculation
	float timer = 0.0f;
	//is the animation playing?
	bool isPlaying = false;

	//the gameObject's renderer
	Renderer* renderer;
	void Awake(){
		this->renderer = GetComponent<Renderer>();
	}

	void Start(){

	}

	void SetAnimationCoordinates(){
		//sets the renderer position;
		renderer->SetTileCoordinates(animations[currentAnimation]->frames[currentFrame].x,
			animations[currentAnimation]->frames[currentFrame].y);
	}

	void Update(){
		if (isPlaying){
			if (currentAnimation >= 0){
				timer += speed * COUNTER->DeltaTime();
				if (timer > animations[currentAnimation]->frames[currentFrame].duration){
					//calculates the next frame
					timer = timer - animations[currentAnimation]->frames[currentFrame].duration;
					currentFrame += 1;
					if (currentFrame >= animations[currentAnimation]->frameCount){
						currentFrame = 0;
					}
					SetAnimationCoordinates();
				}
			}
		}
	}
public:
	//resumes or starts the animation
	void Play(){
		if (!isPlaying)
			isPlaying = true;
	}

	//pauses the animation
	void Pause(){
		if (isPlaying)
			isPlaying = false;
	}

	//Stops the animation and goes back to its first frame
	void Stop(){
		currentFrame = 0;
		timer = 0;
		Pause();
	}

	//sets the animation speed
	void SetSpeed(float p_speed){
		speed = p_speed;
	}

	void AddAnimation(Animation* animation){
		animationCount+= 1;
		Animation** newArray = new Animation*[animationCount];
		for (int i = 0; i < animationCount - 1; i++)	{
			newArray[i] = animations[i];
		}
		delete[] animations;
		animations = new Animation*[animationCount];
		for (int i = 0; i < animationCount - 1; i++)	{
			animations[i] = newArray[i];
		}
		delete[] newArray;
		animations[animationCount - 1] = animation;
	}

	void SetAnimation(int p_index){
		if (currentAnimation != p_index){
			currentAnimation = p_index;
			currentFrame = 0;
		}
	}

	void SetAnimationNow(int p_index){
		if (currentAnimation != p_index){
			SetAnimation(p_index);
			timer = 0.0f;
			SetAnimationCoordinates();
		}
	}

};