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

    static int numIntroLevels() { return 5;}
    static int numMediumLevels() { return 1;}
    static int numHardLevels() { return 2;}
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
        tile.push_back("xivvwwllxxwx");
        tile.push_back("xixxxwwiiiwx");
        tile.push_back("xixcwxwxxxwx");
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

    static string getIntroL4N()
    {
        return "Meet the Cubesters (Part One)";
    }

    static vector<string> getIntroL4T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxx");
        tile.push_back("xs+++++++++x");
        tile.push_back("x+x+x++x+x+x");
        tile.push_back("x++x++++x++x");
        tile.push_back("x+x+x++x+x+x");
        tile.push_back("x++++++++++x");
        tile.push_back("x++++++++++x");
        tile.push_back("x+x+x++x+x+x");
        tile.push_back("x++x++++x++x");
        tile.push_back("x+x+x++x+x+x");
        tile.push_back("x+++++++++fx");
        tile.push_back("xxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getIntroL4C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xbxxxboxxxox");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xbxxxboxxxox");
        cubesters.push_back("xpxxxpaxxxax");
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xpxxxpaxxxax");
        cubesters.push_back("xxxxxxxxxxxx");
        return cubesters;
    }

    static string getIntroL5N()
    {
        return "Meet the Cubesters (Part Two)";
    }

    static vector<string> getIntroL5T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxx");
        tile.push_back("xs+++++++++x");
        tile.push_back("xt++++++++tx");
        tile.push_back("xtx+x++x+x+x");
        tile.push_back("x++x++++x++x");
        tile.push_back("x+x+x++x+x+x");
        tile.push_back("x++++k+++++x");
        tile.push_back("x+x+x++x+x+x");
        tile.push_back("x++x++++x++x");
        tile.push_back("x+x+x++x+xdx");
        tile.push_back("xtt+++++txfx");
        tile.push_back("xxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getIntroL5C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxyuxxxxx");
        cubesters.push_back("xkxxxxxxxxkx");
        cubesters.push_back("xjxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxlxxxxxxxlx");
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxyuxxxxx");
        cubesters.push_back("xjixxxxxixxx");
        cubesters.push_back("xxxxxxxxxxxx");
        return cubesters;
    }

    static string getMediumL1N()
    {
        return "Medium level 1";
    }

    static vector<string> getMediumL1T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxx");  //y, q, e, z
        tile.push_back("x+i+i+xlcx");
        tile.push_back("x+x+x+x+xx");
        tile.push_back("x+x+x+++xx");
        tile.push_back("x+x+x+xpkx");
        tile.push_back("x+i+i+xxxx");
        tile.push_back("x+x+x+xxxx");
        tile.push_back("x+x++++++x");
        tile.push_back("xsxxx++dfx");
        tile.push_back("xxxxxxxxxx");
        return tile;
    }

    static vector<string> getMediumL1C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxx"); 
        cubesters.push_back("xuxyxuxxxx");
        cubesters.push_back("xxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxx");
        cubesters.push_back("xuxyxuxxxx");
        cubesters.push_back("xxxxxxxxxx");
        cubesters.push_back("xxxrxxxxrx");
        cubesters.push_back("xxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxx");
        return cubesters;
    } 

	static string getHardL1N()
	{
		return "Hard Level 1";
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

    static string getHardL2N()
    {
        return "Hard Level 2";
    }

    static vector<string> getHardL2T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxx");
        tile.push_back("xs+++++++++x");
        tile.push_back("x++++++++++x");
        tile.push_back("xtx+x++x+x+x");
        tile.push_back("x+t++++++t+x");
        tile.push_back("x+x+x++x+x+x");
        tile.push_back("x++++++++++x");
        tile.push_back("x+x+x++x+x+x");
        tile.push_back("x+kx++++x++x");
        tile.push_back("x+x+x++x+xdx");
        tile.push_back("xtt+++++txfx");
        tile.push_back("xxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getHardL2C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxyuxxxxx");
        cubesters.push_back("xrxxxxxxxxrx");
        cubesters.push_back("xjxxxxxxxxxx");
        cubesters.push_back("xxkxxxxxxkxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxlxxxxxxxlx");
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxyuxxxxx");
        cubesters.push_back("xjixxxxxixxx");
        cubesters.push_back("xxxxxxxxxxxx");
        return cubesters;
    }

};