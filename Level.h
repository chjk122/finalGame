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

    static int numIntroLevels() { return 3;}
    static int numMediumLevels() { return 0;}
    static int numHardLevels() { return 1;}
    static int numExtremeLevels() { return 0;}
    static int numDifficulties() { return 4;}


private:
	static string getIntroL1N()
	{
		return "The Start of the Journey";
	}
	static vector<string> getIntroL1T()
	{
		vector<string> tile;
		tile.push_back("+xkvvvf");  //y, q, e, z
        tile.push_back("vv++xxd");
        tile.push_back("+xx+vx+");
        tile.push_back("+xx++x+");
        tile.push_back("+xxv+x+");
        tile.push_back("+xxv+x+");
        tile.push_back("s++++++");
		return tile;
	}
	static vector<string> getIntroL1C()
	{
		vector<string> cubesters;
		cubesters.push_back("xxxxxxx"); 
        cubesters.push_back("xxxxxxx");
        cubesters.push_back("xxxxxxx");
        cubesters.push_back("xxxxxxx");
        cubesters.push_back("xxxxxxx");
        cubesters.push_back("xxxxxxx");
        cubesters.push_back("xxxxxxx");
		return cubesters;
	}

	static string getIntroL2N()
	{
		return "Through the Elements (Part One)";
	}

	static vector<string> getIntroL2T()
	{
		vector<string> tile;
		
        tile.push_back("xxxxxxxxxxxx");	
        tile.push_back("xxxxxxxxxxxx");
        tile.push_back("x+++xvp++xfx");
        tile.push_back("x+xlxwxx+xlx");
        tile.push_back("x+xwxwxx+xpx");
        tile.push_back("x+xwxwxx+x+x");
        tile.push_back("x+xwxwkx+xdx");
        tile.push_back("xlxwxwxx+x+x");
        tile.push_back("xsxwwwxx+c+x");
        tile.push_back("xxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxx");
       
		return tile;
	}

	static vector<string> getIntroL2C()
	{
		vector<string> cubesters;
		cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxx");
        return cubesters;
	}


	static string getIntroL3N()
	{
		return "Through the Elements (Part Two)";
	}

	static vector<string> getIntroL3T()
	{
		vector<string> tile;
		tile.push_back("xxxxxxxxxxxx");
        tile.push_back("xv++wwwvkxfx");
        tile.push_back("xixxwxxx+x+x");
        tile.push_back("xixxwxxx+x+x");
        tile.push_back("xixx+xxx+x+x");
        tile.push_back("xivv+lll+x+x");
        tile.push_back("x+ii+iiiipdx");
        tile.push_back("xivv++llxxwx");
        tile.push_back("xixxxwwiiiwx");
        tile.push_back("xixcwxwxixwx");
        tile.push_back("xsxxwwwwwwwx");
        tile.push_back("xxxxxxxxxxxx");
		return tile;
	}

	static vector<string> getIntroL3C()
	{
    	vector<string> cubesters;
    	cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        return cubesters;
	}

	static string getHard1N()
	{
		return "hard level 1";
	}

	static vector<string> getHardL1T()
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

	static vector<string> getHardL1C()
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