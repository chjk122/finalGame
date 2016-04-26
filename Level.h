#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

class Level
{
private:
	void setMaps(int levelCat, int levelN);
	vector<string> tileMap;
	vector<string> cubesterMap;
	string name;
public:
	Level(int levelCat, int levelN);
	~Level();
	vector<string> getTileMap();
	vector<string> getCubesterMap();
	string getName();

private:
	static string getIntroName()
	{
		return "through the elements";
	}
	static vector<string> getIntroL1T()
	{
		vector<string> tile;
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		tile.push_back("xxxxxxxxxxxxxkiiiiiiiiiiiiiiiiiiiiiiiiix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiix");
		tile.push_back("xixixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix");
		tile.push_back("xixixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxdx");
		tile.push_back("xsiixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxfx");
		tile.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		return tile;
	}
	static vector<string> getIntroL1C()
	{
		vector<string> cubesters;
		cubesters.push_back("aaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("aaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		return cubesters;
	}
};