#include "Stopwatch.h"

Timer::Timer():
begTime(0), endTime(0)
{

}
void Timer::start()
{
	begTime = clock();
}
void Timer::stop()
{
	endTime = clock();
}

unsigned long Timer::elapsedTime()
{
	return ((unsigned long) clock() - begTime) / (CLOCKS_PER_SEC / 1000.0);
}

unsigned long Timer::totalTime()
{
	if(endTime == 0)
		stop();
	return (endTime - begTime)/ (CLOCKS_PER_SEC / 1000.0);
}


Stopwatch::Stopwatch():
timer(0), running(false), timeRunning(0)
{

}
bool Stopwatch::isRunning()
{
	return running;
}
bool Stopwatch::start()
{
	if(!isRunning())
	{
		timer = new Timer();
		timer->start();
		running = true;
		return true;
	}
	return false;
}
bool Stopwatch::pause()
{
	return stop();
}
bool Stopwatch::unpause()
{
	return start();
}
bool Stopwatch::stop()
{
	if(isRunning())
	{
		timer->stop();
		running = false;
		timeRunning += timer->elapsedTime();
		delete timer;
		return true;
	}
	return false;
}
void Stopwatch::reset()
{	
	if(isRunning())
		stop();
	timeRunning = 0;
}
unsigned long Stopwatch::totalTime()
{
	return timeRunning;
}
unsigned long Stopwatch::elapsedTime()
{
	if(isRunning())
		return timeRunning + timer->elapsedTime();
	return timeRunning;
}