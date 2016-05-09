//Master class for statistics

#include "Leaderboard.h"

using namespace std;

class Stats 
{
private:
	bool loggedIn;
	Leaderboard lb;
	PlayerStats player;

public:
	Stats();
	~Stats();
	bool createAccount(string uName, string pass);
	bool login(string username, string password);
	void logout();
	void update(int diff, int lvl, int timesDied, unsigned long timeTaken, bool levelCompleted);
	bool save(bool saveLB = true, bool savePlayer = true);
	bool isLoggedIn();
};
