#pragma once
#include <time.h>
#include <SDL.h>
#define FRAMES_PER_SECOND 1000 / 60
#define COUNTER Counter::GetInstance()

/*-Counter has the information regarding
  time, such as the elapsed time since
  the start of the game.*/
class Counter
{
public:
	~Counter();
	// Returns the time elapsed since the start of the game
	double Elapsed();
	static Counter* GetInstance();
	void SUpdate();
	void EUpdate();
	double DeltaTime();

private:
	double m_cps = CLOCKS_PER_SEC;
	double m_start = clock();
	double m_past;
	double m_elapsed = 0.0f;
	double m_deltaTime = 0.0f;
	static Counter* instance;

	Counter();	
};

