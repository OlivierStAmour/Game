#ifndef TIMER
#define TIMER

#include <SDL.h>

class Timer
{
public:
	Timer();
	~Timer();
	//Various timer actions
	void start();
	void stop();
	void pause();
	void unpause();
	//Acces to the timer's time
	Uint32 getTicks();
	//Access to the timer status
	bool isStarted();
	bool isPaused();

private:
	//Clock timer when the timer started
	Uint32 startTicks_;
	//Clock timer when the timer paused
	Uint32 pauseTicks_;
	//Clock status
	bool paused_;
	bool started_;

};


#endif
