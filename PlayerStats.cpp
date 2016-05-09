#include "PlayerStats.h"

using namespace std;
// int main()
// {
	// PlayerStats pStat;
	// if(pStat.createAccount("chjk122", "ekksdee"))
	// {
	// 	cout << "ACCOUNT CREATED FOR \"username\"" << endl;
	// 	// pStat.save();
	// }
	// else
	// {
	// 	if(pStat.login("chjk122", "ekksdee"))
	// 	{
	// 		cout << "logged in" << endl;
	// 	}
	// 	else
	// 		cout << "stop trying to guess my password <(*.*)/" << endl;
	// }
	// pStat.save();

// 	return 0;
// }

PlayerStats::PlayerStats():
levelStats(0), username(""), password("")  
{

}

PlayerStats::~PlayerStats()
{
	for(int x = 0; x < levelStats.size(); x++)
	{
		delete levelStats[x];
	}
	levelStats.clear();
}

string PlayerStats::encrypt(string msg, string const& key)
{
    // if(key.empty())
    //     return msg;
    
    // for (string::size_type i = 0; i < msg.size(); ++i)
    //     msg[i] ^= key[i%key.size()];
    return msg;
}

string PlayerStats::decrypt(string const& msg, string const& key)
{
    return encrypt(msg, key); // xor so ez pz
}

bool PlayerStats::login(string uName, string pass)
{
	username = uName;
	password = pass;
	string line;
	string fileName = fullPath(username);
	ifstream myfile(fileName.c_str());

	if (myfile.is_open() && getline(myfile, line) && line.size() > 0) //password is now in line
	{
		// cout << "comparing " << pass << " with " << encrypt(line, username) << endl;
		if(pass == encrypt(line, username))
		{
			getline(myfile, line); //new line
			getline(myfile, line); //line with numLevelsBeaten
			stringstream ss(line);
			int numLevelsBeaten;
			ss >> numLevelsBeaten;
			for(int x = 0; x < numLevelsBeaten; x++)
			{
				LevelStats *lStat = new LevelStats();
				lStat->read(myfile);
				levelStats.push_back(lStat);
			}
			myfile.close();
			return true;
		}
	}
	myfile.close();
	cout << "username doesnt exist" << endl;
	return false;
}

void PlayerStats::update(int diff, int lvl, int timesDied, unsigned long timeTaken, bool levelCompleted)
{
	//see if level exists
	for(int x = 0; x < levelStats.size(); x++)
	{
		if(levelStats[x]->is(diff, lvl))
		{
			levelStats[x]->update(timesDied, timeTaken, levelCompleted);
			return;
		}
	}
	LevelStats *newLevel = new LevelStats();
	newLevel->create(diff, lvl, timesDied, timeTaken, levelCompleted);
	levelStats.push_back(newLevel);

}

bool comparePtr(LevelStats* a, LevelStats* b)
{
	return (*a < *b);
}

void PlayerStats::save()
{
	sort(levelStats.begin(), levelStats.end(), comparePtr);
	ofstream myfile;
	string fileName = fullPath(username);
	myfile.open(fileName.c_str());
	// without the cstr can start printint hex to file
	myfile << encrypt(password, username).c_str() << "\n\n";
	myfile << levelStats.size() << endl;

	for(int x = 0; x < levelStats.size(); x++)
	{
		levelStats[x]->write(myfile);
	}

	myfile.close();
}

string PlayerStats::getName()
{
	return username;
}

bool PlayerStats::createAccount(string uName, string pass)
{
	string fileName = fullPath(uName);
	ifstream myfile(fileName.c_str());
	string line;
	if (myfile.is_open() && getline(myfile, line) && line.size() > 0)
	{
		password = "";
		username = "";
		return false; //account already exists
	}
	else
	{
		//you can create your account
		password = pass;
		username = uName;
		return true;
	}
	return false;
}