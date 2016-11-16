#include "Counter.h"

Counter* Counter::instance = nullptr;

Counter::Counter()
{
	m_elapsed = 0.0;
}


Counter::~Counter()
{
}

Counter* Counter::GetInstance(){
	if (instance == nullptr)
		instance = new Counter();
	return instance;
}

void Counter::SUpdate(){
	m_start = SDL_GetTicks();
}

void Counter::EUpdate(){
	m_past = (SDL_GetTicks() - m_start);
	if (FRAMES_PER_SECOND > m_past){
		SDL_Delay(FRAMES_PER_SECOND - m_past);
	}
	m_elapsed = SDL_GetTicks();
	m_deltaTime = (m_elapsed - m_start) / 1000;
}

//Returns the time betweeen each clock
double Counter::DeltaTime(){
	return m_deltaTime;
}

// Returns the time elapsed since the start of the game
double Counter::Elapsed()
{
	return m_elapsed;
}
