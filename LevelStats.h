#ifndef LEVELSTATS_H
#define LEVELSTATS_H

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class LevelStats 
{
protected:
	int difficulty;
	int levelNum;
	int timesBeaten;
	int minDeaths;
	int totalDeaths;
	unsigned long minTime;
	unsigned long totalTime;

public:
	LevelStats();
	virtual ~LevelStats();
	virtual bool read(ifstream& file);
	virtual void create(int diff, int lvl, int timesDied, unsigned long timeTaken, bool levelCompleted);
	virtual void update(int timesDied, unsigned long timeTaken, bool levelCompleted);
	virtual bool write(ofstream& file);
	virtual bool is(int diff, int lvl);
	virtual void print();
	// bool compare(LevelStats& rhs);
	virtual bool operator < (const LevelStats& rhs) const
    {
    	if(difficulty != rhs.difficulty)
    		return difficulty < rhs.difficulty;
    	return levelNum < rhs.levelNum;
    }
};

class LeaderboardStats : public LevelStats
{
protected:
	string username;
public:
	LeaderboardStats();
	virtual ~LeaderboardStats();
	virtual bool read(ifstream& file);
	virtual void create(string uName, int timesDied, unsigned long timeTaken);
	virtual void update(int timesDied, unsigned long timeTaken);
	virtual bool write(ofstream& file);
	virtual bool is(string uName);
	virtual void print();
	virtual bool operator < (const LeaderboardStats& rhs) const
    {
    	//now compares deaths and time
    	if(minDeaths != rhs.minDeaths)
    		return minDeaths < rhs.minDeaths;
    	return minTime < rhs.minTime;

        // return (minDeaths <= rhs.minDeaths && minTime < rhs.minTime); 
    }
};

#endif // #ifndef __LevelStats_h_