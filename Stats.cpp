#include "Stats.h"

Stats::Stats():
loggedIn(false), lb(), player()
{
}
Stats::~Stats()
{

}

bool Stats::createAccount(string username, string password)
{
	if(loggedIn)
		return false; //already logged in should logout first
	loggedIn = player.createAccount(username, password);
	return loggedIn;
}
bool Stats::login(string username, string password)
{
	if(loggedIn)
		return false; //already logged in should logout first
	loggedIn = player.login(username, password);
	return loggedIn;
}
void Stats::logout()
{
	if(!loggedIn)
		return; //nothing to logout of
	save(false, true); // save the old player stats
	player = PlayerStats(); //be ready for new player
	loggedIn = false;
}
void Stats::update(int diff, int lvl, int timesDied, unsigned long timeTaken, bool levelCompleted)
{
	if(loggedIn)
	{
		player.update(diff, lvl, timesDied, timeTaken, levelCompleted);
		if(levelCompleted)
		{
			lb.update(diff, lvl, player.getName(), timesDied, timeTaken);
		}
	}
}
bool Stats::save(bool saveLB, bool savePlayer)
{
	if(saveLB && loggedIn)
		lb.save();
	if(savePlayer && loggedIn)
		player.save();
	return loggedIn;
}

bool Stats::isLoggedIn()
{
	return loggedIn;
}