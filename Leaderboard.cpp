#include "Leaderboard.h"

using namespace std;

// int main()
// {
// 	cout << "running" << endl;
// 	Leaderboard lb;
// 	lb.update(1,1,"chjk122",0, 6700);
// 	lb.update(1,1,"master",0, 1000);
// 	lb.update(1,2,"master",0, 2000);
// 	lb.update(1,3,"master",1, 3000);
// 	lb.update(1,3,"noob",3, 3000);
// 	lb.update(1,3,"SuperNoob",10, 90000);
// 	lb.update(1,3,"chjk122",0, 6900);
// 	lb.update(1,3,"master2",1, 2999);
// 	lb.update(1,3,"noob2",3, 2999);
// 	lb.update(1,3,"SuperNoob2",10, 89999);
// 	lb.update(1,3,"chjk1222",0, 6899);
// 	lb.update(1,3,"master3",1, 3001);
// 	lb.update(1,3,"noob3",3, 3001);
// 	lb.update(1,3,"SuperNoob3",10, 90001);
// 	lb.update(1,3,"chjk1223",0, 6901);
// 	lb.update(1,4,"master",0, 4000);
// 	lb.update(1,5,"master",0, 5000);
// 	lb.update(1,6,"chjk122",0, 6800);
// 	lb.update(1,3,"chjk122",0, 6900);
// 	lb.update(1,2,"chjk122",0, 300);
// 	lb.save();
// 	return 0;
// }


Leaderboard::Leaderboard()
{
	load();
}
Leaderboard::~Leaderboard()
{
	for(map< pair<int, int>, vector<LeaderboardStats *>  >::iterator it = leaderboard.begin();
    	it != leaderboard.end(); ++it)
	{
		for(int x = 0; x < it->second.size(); ++x)
		{
			delete it->second[x];
		}
		it->second.clear();
	}
}
bool Leaderboard::load()
{
	string line;
	string fileName = PlayerStats::fullPath("Leaderboard");
	ifstream myfile(fileName.c_str());

	if (myfile.is_open() && getline(myfile, line) && line.size() > 0) //gets the total number levels saved
	{
		cout << "loading the leaderboard" << endl;

		int totalLevels;
		stringstream ss(line);
		ss >> totalLevels;

		if(totalLevels == 0)
		{
			cout << "loaded leaderboard with 0 levels" << endl;
			return false;
		}
		int levelsToLoad;
		int difficulty;
		int levelNum;
		vector<LeaderboardStats *> lbStats;
		pair <int,int> levelInfo;
		while(totalLevels > 0)
		{
			getline(myfile, line); //new line
			getline(myfile, line); // number of levels coming up
			ss.str(std::string());
			ss.clear();
			ss.str(line);
			ss >> levelsToLoad;

			getline(myfile, line); //level diff and num
			ss.str(std::string());
			ss.clear();
			ss.str(line);
			ss >> difficulty;
			ss >> levelNum;
			levelInfo = make_pair(difficulty,levelNum);

			for(int x = 0; x < levelsToLoad; x++)
			{
				totalLevels--;
				// getline(myfile, line); //ignore the ranking value (now a new line)
				LeaderboardStats *lbStat = new LeaderboardStats();
				lbStat->read(myfile);
				lbStats.push_back(lbStat);
			}
			leaderboard[levelInfo] = lbStats; //copy the info into the map
			lbStats.clear(); //reset the vector to empty
			cout << "levels left to load: " << totalLevels << endl;
		}
		myfile.close();
		return true;
	}
	else //leaderboard info doesnt exist
	{
		cout << "creating the Leaderboard" << endl;
		//write to file ??? maybe set up to save when ready??
	}
	myfile.close();
	return false;
}
void Leaderboard::update(int diff, int lvl, string uName, int timesDied, unsigned long timeTaken)
{
	pair <int,int> levelPair = make_pair(diff,lvl);
	vector<LeaderboardStats *> temp = leaderboard[levelPair];
	for(int x =0; x < temp.size(); x++)
	{
		if(temp[x]->is(uName))
		{
			temp[x]->update(timesDied, timeTaken);
			return;
		}
	}
	//new to the highscore
	LeaderboardStats *lbStat = new LeaderboardStats();
	lbStat->create(uName, timesDied, timeTaken);
	temp.push_back(lbStat);
	leaderboard[levelPair] = temp;
}


bool comparePtr2(LeaderboardStats* a, LeaderboardStats* b)
{
	return (*a < *b);
}

void Leaderboard::save()
{
	ofstream myfile;
	string fileName = PlayerStats::fullPath("Leaderboard");
	myfile.open(fileName.c_str());
	// without the cstr can start printing hex to file
	myfile << totalNumStats() << "\n" << endl;

	for(map< pair<int, int>, vector<LeaderboardStats *>  >::iterator it = leaderboard.begin();
        it != leaderboard.end(); ++it)
	{
		//sort the vector ?????
		sort(it->second.begin(),it->second.end(), comparePtr2);


		myfile << it->second.size() << endl;
		myfile << it->first.first << " " << it->first.second << endl;
		for(int x = 0; x < it->second.size(); ++x)
		{
			// myfile << endl; //ignore the newline
			it->second[x]->write(myfile);
		}
		myfile << endl; //newline after each level set of info
	}

	myfile.close();
}

void Leaderboard::print()
{
	for(map< pair<int, int>, vector<LeaderboardStats *>  >::const_iterator it = leaderboard.begin();
    	it != leaderboard.end(); ++it)
	{
		cout << it->first.first << ", " << it->first.second << " contains" << endl;
		for(int x = 0; x < it->second.size(); ++x)
		{
			cout << "\t";
			it->second[x]->print();
		}
	}
}

int Leaderboard::totalNumStats()
{
	int count = 0;
	for(map< pair<int, int>, vector<LeaderboardStats *>  >::const_iterator it = leaderboard.begin();
    	it != leaderboard.end(); ++it)
	{
		count += it->second.size();
	}
	return count;
}
int Leaderboard::numStats(int diff, int levelNum)
{
	for(map< pair<int, int>, vector<LeaderboardStats *>  >::const_iterator it = leaderboard.begin();
   		it != leaderboard.end(); ++it)
	{
		if(it->first.first == diff && it->first.second == levelNum)
		{
			return it->second.size();
		}
	}
	return -1;
}
