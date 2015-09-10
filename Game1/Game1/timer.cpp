#include "timer.h"

Timer::Timer()
{
	startTicks_ = 0;	
	pauseTicks_ = 0;
	paused_ = false;
	started_ = false;
}



Timer::~Timer()
{
}


void Timer::start()
{
	started_ = true;
	paused_ = false;
	startTicks_ = SDL_GetTicks();
	pauseTicks_ = 0;
}



void Timer::stop()
{
	started_ = false;
	paused_ = false;
	startTicks_ = 0;
	pauseTicks_ = 0;
}



void Timer::pause()
{
	if (started_ && !paused_)
	{
		paused_ = true;
		pauseTicks_ = SDL_GetTicks() - startTicks_;
		startTicks_ = 0;
	}
}



void Timer::unpause()
{
	if (started_ && paused_)
	{
		paused_ = false;
		startTicks_ = SDL_GetTicks() - pauseTicks_;
		pauseTicks_ = 0;
	}	
}



Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (started_)
	{
		//If the timer is paused
		if (paused_)
		{
			//Return the number of ticks when the timer was paused
			time = pauseTicks_;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - startTicks_;
		}
	}

	return time;
}



bool Timer::isStarted()
{
	return started_;
}



bool Timer::isPaused()
{
	return paused_ && started_;
}
