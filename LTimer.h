#ifndef LTIMER_H
#define LTIMER_H

#include <stdio.h>
#include "SDL2/SDL_timer.h"

class LTimer
{
	public:
		LTimer();

		void start();
		void stop();
		void pause();
		void unpause();

		//Timer's time
		Uint32 getTicks();

		bool isStarted();
		bool isPaused();
	protected:
		Uint32 mStartTicks;
		Uint32 mPausedTicks;

		bool mPaused;
		bool mStarted;
};

#endif
