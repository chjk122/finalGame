#include "LevelStats.h"
#include <unistd.h>
#include <vector>
#define GetCurrentDir getcwd

using namespace std;

class PlayerStats 
{
private:
	vector<LevelStats *> levelStats;
	string username;
	string password;
	//settings

	string encrypt(string msg, string const& key);
	string decrypt(string const& msg, string const& key);

public:
	PlayerStats();
	~PlayerStats();
	bool login(string username, string password);
	bool createAccount(string uName, string pass);
	void update(int diff, int lvl, int timesDied, unsigned long timeTaken, bool levelCompleted);
	void save();
	string getName();

	static bool nameAvailable(string& name)
	{
		string fileName = fullPath(name);
		ifstream file(fileName.c_str());
		return file.is_open();
	}
	static string exePath()
	{
	     char cCurrentPath[FILENAME_MAX];

		 if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	     {
	     	return "";
	     }

		// cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

		// printf ("The current working directory is %s", cCurrentPath);
		string str(cCurrentPath);
		return str;
	}
	static string fullPath(string fileName)
	{
		return exePath() + "/saves/" + fileName + ".txt";
	}
};
