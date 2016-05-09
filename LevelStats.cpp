#include "LevelStats.h"

using namespace std;

LevelStats::LevelStats():
difficulty(-1), levelNum(-1), timesBeaten(0), minDeaths(-1), totalDeaths(0), minTime(0), totalTime(0)
{

}

LevelStats::~LevelStats()
{
	// cout << "LEVEL " << difficulty << " " << levelNum << " DELETED" << endl;
}

bool LevelStats::read(ifstream& file)
{
	if (file.is_open())
	{
		string line;
		getline(file, line); // get rid of new line before level info
		getline(file, line); // get the line with diff and levelNum

		stringstream ss(line); // create string stream to pipe out stats
		ss >> difficulty;
		ss >> levelNum;

		getline(file, line); //line with timesBeaten
		ss.str(std::string());
		ss.clear();
		ss.str(line);
		ss >> timesBeaten;

		getline(file, line); //line with minDeaths
		ss.str(std::string());
		ss.clear();
		ss.str(line);
		ss >> minDeaths;

		getline(file, line); //line with totalDeaths
		ss.str(std::string());
		ss.clear();
		ss.str(line);
		ss >> totalDeaths;

		getline(file, line); //line with minTime
		ss.str(std::string());
		ss.clear();
		ss.str(line);
		ss >> minTime;

		getline(file, line); //line with totalTime
		ss.str(std::string());
		ss.clear();
		ss.str(line);
		ss >> totalTime;
		return true;
	}
	else
	{
		cout << "level read Failed" << endl;
		return false;
	}
}

void LevelStats::create(int diff, int lvl, int timesDied, unsigned long timeTaken, bool levelCompleted)
{
	difficulty = diff;
	levelNum = lvl;
	update(timesDied, timeTaken, levelCompleted);
}



void LevelStats::update(int timesDied, unsigned long timeTaken, bool levelCompleted)
{
	if(levelCompleted)
	{
		// first time completing the level
		timesBeaten += 1;
		if(timesBeaten == 1) //first time beating a level
		{
			minDeaths = timesDied;
			minTime = timeTaken;
		}
		// everytime after the first
		else
		{
			minDeaths = min(timesDied, minDeaths);
			minTime = min(timeTaken, minTime);
		}
	}
	totalDeaths += timesDied;
	totalTime += timeTaken;
}

bool LevelStats::write(ofstream& file)
{
	// without the cstr can start printint hex to file
	file << "\n";
	file << difficulty << " " << levelNum << "\n";
	file << "\t" << timesBeaten << "\n";
	file << "\t" << minDeaths << "\n";
	file << "\t" << totalDeaths << "\n";
	file << "\t" << minTime << "\n";
	file << "\t" << totalTime << "\n";
}

bool LevelStats::is(int diff, int lvl)
{
	return (difficulty == diff && levelNum == lvl);
}

void LevelStats::print()
{
	cout << "difficulty is " << difficulty;
	cout << " and levelNum is " << levelNum << endl;
	cout << "\tminDeaths is " << minDeaths << endl;
	cout << "\ttotalDeaths is " << totalDeaths << endl;
	cout << "\tminTime is " << minTime << endl;
	cout << "\ttotalTime is " << totalTime << endl;

}

LeaderboardStats::LeaderboardStats():
LevelStats(), username("")
{

}
LeaderboardStats::~LeaderboardStats()
{
	// cout << "deleted lbs stat " <<  username << " " << minTime << endl;
}
bool LeaderboardStats::read(ifstream& file)
{
	if (file.is_open())
	{
		string line;
		getline(file, line); // should be the username

	    // remove(line.begin(), line.end(), ' ');

		username = line;
		getline(file, line); // get the line with minDeaths

		stringstream ss(line); // create string stream to pipe out number
		ss >> minDeaths;

		getline(file, line); //line with minTime
		ss.str(std::string());
		ss.clear();
		ss.str(line);
		ss >> minTime;
		return true;
	}
	else
	{
		cout << "LeaderboardStats read Failed" << endl;
		return false;
	}
}
void LeaderboardStats::create(string uName, int timesDied, unsigned long timeTaken)
{
	username = uName;
	update(timesDied, timeTaken);
}
void LeaderboardStats::update(int timesDied, unsigned long timeTaken)
{
	//first time being added
	if(minDeaths == -1)
	{
		minDeaths = timesDied;
		minTime = timeTaken;
	}
	else
	{
		if(minDeaths > timesDied)
			minDeaths = timesDied;
		if(minTime > timeTaken)
			minTime = timeTaken;
	}
}

bool LeaderboardStats::write(ofstream& file)
{
	file << username << "\n";
	file << "\t" << minDeaths << "\n";
	file << "\t" << minTime << "\n";
}

bool LeaderboardStats::is(string uName)
{
	return (uName == username);
}

void LeaderboardStats::print()
{
	cout << "Uname: " << username << ", " << minDeaths << ", " << minTime << endl;
}