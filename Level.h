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
    static int numMediumLevels() { return 2;}
    static int numHardLevels() { return 3;}
    static int numExtremeLevels() { return 2;}
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
        tile.push_back("x+x+x++x+x+x");
        tile.push_back("x++x++++x++x");
        tile.push_back("x+x+x++x+x+x");
        tile.push_back("x++++k+++++x");
        tile.push_back("x+x+x++x+x+x");
        tile.push_back("x++x++++x++x");
        tile.push_back("x+x+x++x+xdx");
        tile.push_back("x+t+++++txfx");
        tile.push_back("xxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getIntroL5C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxyuxxxxx");
        cubesters.push_back("xkxxxxxxxxkx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxlxxxxxxxlx");
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxyuxxxxx");
        cubesters.push_back("xxixxxxxixxx");
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
        tile.push_back("xxxxxxxxxx");  
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
        cubesters.push_back("xxxlxxxxlx");
        cubesters.push_back("xxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxx");
        return cubesters;
    } 

    static string getMediumL2N()
    {
        return "Medium level 2";
    }

    static vector<string> getMediumL2T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxxx");  
        tile.push_back("xfxlwwwww++++sx");
        tile.push_back("xdxxwxxxxxxxxxx");
        tile.push_back("x+xtwwwwwww++tx");
        tile.push_back("x+xxxvxvxvxxxtx");
        tile.push_back("x++xxxxxxxtxx+x");
        tile.push_back("xx+++xxt+++xx+x");
        tile.push_back("xkx++xx+xx+xp+x");
        tile.push_back("x+x++xp+xc+xx+x");
        tile.push_back("x+x++xx+xx+xx+x");
        tile.push_back("x+x++xv+xl+xp+x");
        tile.push_back("x+x++xx+xx+xx+x");
        tile.push_back("x+ci+xx+xx+xx+x");
        tile.push_back("xxx++++txxt++tx");
        tile.push_back("xxxxxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getMediumL2C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxixxxxxxxxxix"); 
        cubesters.push_back("xxxxxxxxxxxxxjx"); 
        cubesters.push_back("xxxxxxxxxxhxxxx"); 
        cubesters.push_back("xxxxuxxjxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxyxxxxxxxxxxx"); 
        cubesters.push_back("xxxxuxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxyxxxjxxhxxjx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
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
        cubesters.push_back("xhxxxxxxxxxx");
        cubesters.push_back("xxixxxxxxixx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxrxxxxxxxrx");
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxyuxxxxx");
        cubesters.push_back("xhkxxxxxkxxx");
        cubesters.push_back("xxxxxxxxxxxx");
        return cubesters;
    }

    static string getHardL3N()
    {
        return "Hard level 3";
    }

    static vector<string> getHardL3T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxxx");  
        tile.push_back("xfxxxxxii+++++x");
        tile.push_back("xdxk+++ii++ll+x");
        tile.push_back("xdxxxxxii++ll+x");
        tile.push_back("xd++++++++++++x");
        tile.push_back("x+xxxxxixxxxxxx");
        tile.push_back("xixxxxxixxxxxxx");
        tile.push_back("xixkt++++++++tx");
        tile.push_back("xixxxxxxxxxxxxx");
        tile.push_back("xillllllll++++x");
        tile.push_back("xillllllll++++x");
        tile.push_back("xillllllll++++x");
        tile.push_back("xillllllll++++x");
        tile.push_back("xst++++++++txkx");
        tile.push_back("xxxxxxxxxxxxxxx");
    
        return tile;
    }

    static vector<string> getHardL3C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxaxcaxcxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxlxxxxaxcaxclx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxkxxxxxxxxkx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xrxxxxxrxabaxbx"); 
        cubesters.push_back("xlxxlxxxxxxxxxx"); 
        cubesters.push_back("xrxxxxxxraxaxxx"); 
        cubesters.push_back("xlxxxxxxxlbxxbx"); 
        cubesters.push_back("xxixxxxxxxxixxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        return cubesters;
    } 

    static string getHardL4N()
    {
        return "Hard level 4";
    }

    static vector<string> getHardL4T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxxx");  
        tile.push_back("xxxxxxxxxxxxpsx");
        tile.push_back("xxxxxxxxxxxxxpx");
        tile.push_back("xxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxx");
        tile.push_back("xfxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxx");
    
        return tile;
    }

    static vector<string> getHardL4C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxxxxx"); 
        return cubesters;
    } 

    static string getExtremeL4N()
    {
        return "Starting to Get Spicy";
    }

    static vector<string> getExtremeL4T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxx");
        tile.push_back("xfds+++++++x");
        tile.push_back("xxxxxxxxxx+x");
        tile.push_back("++++++x++++x");
        tile.push_back("++++++x++++x");
        tile.push_back("+++xx+x++++x");
        tile.push_back("+++x++x++++x");
        tile.push_back("++x++xx++++x");
        tile.push_back("+++x++x++++x");
        tile.push_back("x+++x+x++++x");
        tile.push_back("xk++x++++++x");
        tile.push_back("xxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getExtremeL4C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxaAaAmMmM");
        cubesters.push_back("x++++++++++x");
        cubesters.push_back("xxxxaAaAmMmM");
        cubesters.push_back("axxyaxly+++l");
        cubesters.push_back("bx+xbxxYu++x");
        cubesters.push_back("mxxxmxr+Uy+r");
        cubesters.push_back("nx+xnxx++Yux");
        cubesters.push_back("ax+xaxly++Ul");
        cubesters.push_back("bx+xbxxYu++x");
        cubesters.push_back("mxxxmxlxUy+l");
        cubesters.push_back("nxxxnx+++Yux");
        cubesters.push_back("xxxyxxxxxxUx");
        return cubesters;
    }

    static string getExtremeL5N()
    {
        return "What Did I do to Deserve This?";
    }

    static vector<string> getExtremeL5T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxxxx");
        tile.push_back("x+kx+++++++++++x");
        tile.push_back("x++x+xxxxxxxxx+x");
        tile.push_back("x++x+xt+t+++tx+x");
        tile.push_back("x++x+x+xxxxx+x+x");
        tile.push_back("xk+x+x+xt++xtx+x");
        tile.push_back("x++x+x+x+xtxtx+x");
        tile.push_back("x++x+x+xxx+x+x+x");
        tile.push_back("x++x+xtxxx+x+x+x");
        tile.push_back("x++xtx+++t+x+x+x");
        tile.push_back("x+kx+xxxxxxx+x+x");
        tile.push_back("x++xt++++tt+tx+x");
        tile.push_back("x++x+xxxxxxxxx+x");
        tile.push_back("x++++xfddd+++++x");
        tile.push_back("xxxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getExtremeL5C()
    {
        vector<string> cubesters;
        cubesters.push_back("aAaAxxxxxxxxbxbx");
        cubesters.push_back("xxxxaaxxxxxxxxxx");
        cubesters.push_back("aAaAaaxxxxxxbxbx");
        cubesters.push_back("bBbBxxhxixxxixxx");
        cubesters.push_back("xxxxxxxxxxxxxaxa");
        cubesters.push_back("bBbBxxxxixxxixxx");
        cubesters.push_back("cCcCxxxxxxjxjaxa");
        cubesters.push_back("xxxxxxxxsxxxxmxm");
        cubesters.push_back("cCcCxxhxxxxxxxxx");
        cubesters.push_back("dDdDkxxxxkxxxmxm");
        cubesters.push_back("xxxxxxxxxxxxxaxa");
        cubesters.push_back("dDdDkxxxxkjxjxxx");
        cubesters.push_back("x++x+xxOxOxxxaxa");
        cubesters.push_back("x++++xxMmMmxxxxx");
        cubesters.push_back("xxxxxxxOxOxxxxxx");
        cubesters.push_back("xxxxxxxMmMmxxxxx");
        return cubesters;
    }

    // static string getHardL4N()
    // {
    //     return "Hard level 4";
    // }

    // static vector<string> getHardL4T()
    // {
    //     vector<string> tile;
    //     tile.push_back("xxxxxxxxxxxxxxx");  
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    //     tile.push_back("xxxxxxxxxxxxxxx");
    
    //     return tile;
    // }

    // static vector<string> getHardL3C()
    // {
    //     vector<string> cubesters;
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     cubesters.push_back("xxxxxxxxxxxxxxx"); 
    //     return cubesters;
    // } 





};