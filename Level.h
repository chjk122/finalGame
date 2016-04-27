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
	static string getIntroL1N()
	{
		return "through the elements";
	}
	static vector<string> getIntroL1T()
	{
		vector<string> tile;
		tile.push_back("xxxxxxx");  //y, q, e, z
        tile.push_back("xwwwwwx");
        tile.push_back("xwxwxwx");
        tile.push_back("xwxwxwx");
        tile.push_back("xlxwxvx");
        tile.push_back("xlxwxdx");
        tile.push_back("xsxkxfx");
		return tile;
	}
	static vector<string> getIntroL1C()
	{
		vector<string> cubesters;
		cubesters.push_back("abxxabx"); 
        cubesters.push_back("cdxxcdx");
        cubesters.push_back("xxxxxxx");
        cubesters.push_back("xxxxxxx");
        cubesters.push_back("abxxabx");
        cubesters.push_back("cdxxcdx");
        cubesters.push_back("xxxxxxx");
		return cubesters;
	}
};