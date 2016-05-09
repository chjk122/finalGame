#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

class Timer
{
private:
	unsigned long begTime;
	unsigned long endTime;

public:
	Timer();
	void start();
	void stop();
	unsigned long elapsedTime();
	unsigned long totalTime();

};

class Stopwatch {
private:
	Timer *timer;
	bool running;
	unsigned long timeRunning;
public:
	Stopwatch();
	bool isRunning();
	bool start();
	bool pause();
	bool unpause();
	bool stop();
	void reset();
	unsigned long totalTime();
	unsigned long elapsedTime();
};