#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

class Level
{
	static string getLevel1Name()
	{
		return "through the elements";
	}
	static vector<string> getLevel1Tiles()
	{
		vector<string> tile;
		tile->push_back("+++wwwlkxf");
		tile->push_back("ixxwxxxxxv");
		tile->push_back("ixxwxxxxx+");
		tile->push_back("ixxwxxxxx+");
		tile->push_back("ivvwlllxx+");
		tile->push_back("++++++++pd");
		tile->push_back("ivv++llxxp");
		tile->push_back("ixx+++xxx+");
		tile->push_back("ixxxx+xxx+");
		tile->push_back("sxxc++++++");
		return tile;
	}
	static vector<string> getLevel1Cubesters()
	{
		vector<string> tile;
		cubesters->push_back("axaxxxxxxx");
		cubesters->push_back("xxxxxxxxxx");
		cubesters->push_back("axaxxxxxxx");
		cubesters->push_back("xxxxxxxxxx");
		cubesters->push_back("xxxxxxxxxx");
		cubesters->push_back("xxxxxxxxxx");
		cubesters->push_back("xxxxxxxxxx");
		cubesters->push_back("xxxxxxxxxx");
		cubesters->push_back("xxxxxxxxxx");
		cubesters->push_back("xxxxxxxxxx");
		return tile;
	}
};