#include "PlayerStats.h"
#include <utility>      // std::pair, std::get
#include <map>

using namespace std;

class Leaderboard 
{
private:
	//diff and levelNum give list of leaderboard stats for that level
	map< pair<int, int>, vector<LeaderboardStats *> > leaderboard;

public:
	Leaderboard();
	~Leaderboard();
	bool load();
	void update(int diff, int lvl, string uName, int timesDied, unsigned long timeTaken);
	void save();
	void print();
	int totalNumStats();
	int numStats(int diff, int levelNum);
};
