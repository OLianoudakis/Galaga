#include "Timer.h"

Timer* Timer::sInstance = NULL;

Timer* Timer::Instance()
{
    if (sInstance == NULL)
    {
        sInstance = new Timer();
    }

    return sInstance;
}

void Timer::Release()
{
    delete sInstance;
    sInstance = NULL;
}

Timer::Timer()
{
    Reset();
    mTimeScale = 1.0f;
}

Timer::~Timer()
{

}

void Timer::Reset()
{
    mStartTicks = SDL_GetTicks();
    mElapsedTicks = 0;
    mDeltaTime = 0.0f;
}
// current time passed
float Timer::DeltaTime()
{
    return mDeltaTime;
}

void Timer::TimeScale(float t)
{
    mTimeScale = t;
}

float Timer::TimeScale()
{
    return mTimeScale;
}
//calculate delta time
void Timer::Update()
{
    mElapsedTicks = SDL_GetTicks() - mStartTicks;

    //use this for time dependent translations and not frame dependent
    mDeltaTime = mElapsedTicks * 0.001f; //convert ms to float
    
}