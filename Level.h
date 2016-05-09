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
    static string getName(int diff, int level)
    {
        Level temp(diff, level);
        return temp.getName();
    }

    static int numLevels(int diff)
    {
        if(diff == 1)      {return 6;} // intro
        else if(diff == 2) {return 6;} // medium
        else if(diff == 3) {return 5;} // hard
        else if(diff == 4) {return 5;} // extreme
        else if(diff == 5) {return 2;} // credit
    }
    static string difficultyName(int diff)
    {
        if(diff == 1)      {return "intro";}
        else if(diff == 2) {return "medium";}
        else if(diff == 3) {return "hard";}
        else if(diff == 4) {return "extreme";}
        else if(diff == 5) {return "credit";}
    }
    static int numDifficulties() { return 4;}

    static vector<string> getLoadingLevelT()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxx");
        tile.push_back("xwlpvplwx");  //y, q, e, z
        tile.push_back("xwiisiiwx");
        tile.push_back("xt*****tx");
        tile.push_back("xbd+++kdx");
        tile.push_back("xpcrfrcpx");
        tile.push_back("x*++x++*x");
        tile.push_back("x*x+++x*x");
        tile.push_back("xxxxxxxxx");
        return tile;
    }

    static vector<string> getLoadingLevelC()
    {
        vector<string> cubesters;
        cubesters.push_back("aaxxxxxdd");
        cubesters.push_back("aaxxxxxdd");  //y, q, e, z
        cubesters.push_back("xrxrxlxlx");
        cubesters.push_back("xixxxxxix");
        cubesters.push_back("mmxxxxxpp");
        cubesters.push_back("mmxxxxxpp");
        cubesters.push_back("xy++x++ux");
        cubesters.push_back("x+x+++x+x");
        cubesters.push_back("xyxxxxxux");
        return cubesters;
    }

private:
    static string getIntroL1N()
    {
        return "Learn How to walk";
    }
    static vector<string> getIntroL1T()
    {
        vector<string> tile;
        tile.push_back("xxkvvvf");  //y, q, e, z
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
        return "What Almost Kills You";
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
        return "Through the Elements";
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
        tile.push_back("x+ii+iiipxdx");
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
        return "Meet the Square Cubester";
    }

    static vector<string> getIntroL4T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxx");
        tile.push_back("xs*********x");
        tile.push_back("x*x+x**x+x*x");
        tile.push_back("x*+x+**+x+*x");
        tile.push_back("x*x+x**x+x*x");
        tile.push_back("x**********x");
        tile.push_back("x**********x");
        tile.push_back("x*x+x**x+x*x");
        tile.push_back("x*+x+**+x+*x");
        tile.push_back("x*x+x**x+x*x");
        tile.push_back("x*********fx");
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
        return "Meet the Line Cubester";
    }

    static vector<string> getIntroL5T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxx");
        tile.push_back("xxxxxxxxx");
        tile.push_back("xxxxxxxxx");
        tile.push_back("xxxxxxxxx");
        tile.push_back("xx*+*+*+x");
        tile.push_back("xs*+*+*+f");
        tile.push_back("xx*+*+*+x");
        tile.push_back("xxxxxxxxx");
        tile.push_back("xxxxxxxxx");
        return tile;
    }

    static vector<string> getIntroL5C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxx");
        cubesters.push_back("xxxxxxxxx");
        cubesters.push_back("xxyxuxyxx");
        cubesters.push_back("xxxxxxxxx");
        cubesters.push_back("xx++++++x");
        cubesters.push_back("x++++++++");
        cubesters.push_back("xx++++++x");
        cubesters.push_back("xxxxxxxxx");
        cubesters.push_back("xxyxuxyxx");
        return cubesters;
    }

    static string getIntroL6N()
    {
        return "Meet the Teleport Cubester";
    }

    static vector<string> getIntroL6T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxx");
        tile.push_back("xxxxxxxxx");
        tile.push_back("xxtxtxtxx");
        tile.push_back("xxxxxxxxx");
        tile.push_back("xx*+*+*+x");
        tile.push_back("xs*+*+*+f");
        tile.push_back("xx*+*+*+x");
        tile.push_back("xxxxxxxxx");
        tile.push_back("xxtxtxtxx");
        return tile;
    }

    static vector<string> getIntroL6C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxx");
        cubesters.push_back("xxxxxxxxx");
        cubesters.push_back("xxjxhxjxx");
        cubesters.push_back("xxxxxxxxx");
        cubesters.push_back("xx++++++x");
        cubesters.push_back("x++++++++");
        cubesters.push_back("xx++++++x");
        cubesters.push_back("xxxxxxxxx");
        cubesters.push_back("xxjxhxjxx");
        return cubesters;
    }

    static string getMediumL1N()
    {
        return "Outrun the Cubester";
    }

    static vector<string> getMediumL1T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxx");
        tile.push_back("x*i*i*xlcx");
        tile.push_back("x*x*x*xwxx");
        tile.push_back("x*x*x*++xx");
        tile.push_back("x*x*x*xpkx");
        tile.push_back("x*i*i*xxxx");
        tile.push_back("x+x+x+xxxx");
        tile.push_back("x+x*****xx");
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


    static string getMediumL2N()
    {
        return "The Crossroad";
    }

    static vector<string> getMediumL2T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxx");
        tile.push_back("xs+++**++++x");
        tile.push_back("xt********tx");
        tile.push_back("xxx+x**x+xxx");
        tile.push_back("x+++x**x+++x");
        tile.push_back("x+xxx**xxx+x");
        tile.push_back("x+*********x");
        tile.push_back("x+xxx**xxx+x");
        tile.push_back("x++++**++++x");
        tile.push_back("x+xxx**xxxdx");
        tile.push_back("xt***b**txfx");
        tile.push_back("xxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getMediumL2C()
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
        cubesters.push_back("xixxxxxxixxx");
        cubesters.push_back("xxxxxxxxxxxx");
        return cubesters;
    }

    static string getMediumL3N()
    {
        return "Remember to Breath";
    }

    static vector<string> getMediumL3T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxxx");  
        tile.push_back("xfxlwwwww++++sx");
        tile.push_back("xdxxwxxxxxxxxxx");
        tile.push_back("x+xtwwwwwww**tx");
        tile.push_back("x+xxxvxvxvxxxtx");
        tile.push_back("x++xxxxxxxtxx*x");
        tile.push_back("xx++*xxt++*xx*x");
        tile.push_back("xkx+*xx*xx*xp*x");
        tile.push_back("x+x+*xp*xc*xx*x");
        tile.push_back("x+x**xx*xx*xx*x");
        tile.push_back("x+x**xv*xl*xp*x");
        tile.push_back("x+x*+xx*xx*xx*x");
        tile.push_back("x+ci+xx*xx*xx*x");
        tile.push_back("xxx*+++txxt++tx");
        tile.push_back("xxxxxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getMediumL3C()
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


    static string getMediumL4N()
    {
        return "Slow and Consistent";
    }

    static vector<string> getMediumL4T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xs*xxxxxxxxxfx");
        tile.push_back("xx**xxxxxxx*+x");
        tile.push_back("xxx**xxxxx**xx");
        tile.push_back("xxxx**xxx**xxx");
        tile.push_back("xxxxx**x**xxxx");
        tile.push_back("xxxxxx***xxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getMediumL4C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxyxxxxxxxxxxx");
        cubesters.push_back("xxxyxxxxxxxyxx");
        cubesters.push_back("xxxxyxxxxxyxxx");
        cubesters.push_back("x+yxxyxxxyxx+x");
        cubesters.push_back("xxyyxxyxyxxy+x");
        cubesters.push_back("xxxyyxxyxxyyxx");
        cubesters.push_back("xxxxyyxxxyyxxx");
        cubesters.push_back("xxyxxyyxyyxxxx");
        cubesters.push_back("xxxyxxy+yxxyxx");
        cubesters.push_back("xxxxyxxxxxyxxx");
        cubesters.push_back("xxxxxyxxxyxxxx");
        cubesters.push_back("xxxxxxyyyxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxx");
        return cubesters;
    } 

    static string getMediumL5N()
    {
        return "Ring of Cubester";
    }

    static vector<string> getMediumL5T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxxxx");
        tile.push_back("x**************x");
        tile.push_back("x**************x");
        tile.push_back("x**+s++++++++**x");
        tile.push_back("x**+d++++++++**x");
        tile.push_back("x**+f******++**x");
        tile.push_back("x**+d******++**x");
        tile.push_back("x**++******++**x");
        tile.push_back("x**++******++**x");
        tile.push_back("x**++******++**x");
        tile.push_back("x**++******++**x");
        tile.push_back("x**++++++++++**x");
        tile.push_back("x**++++++++++**x");
        tile.push_back("x**************x");
        tile.push_back("x**************x");
        tile.push_back("xxxxxxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getMediumL5C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxaAxxxxxxaAxxx");
        cubesters.push_back("xxaxxAxxxxaxxAxx");
        cubesters.push_back("xaxxxxAxxaxxxxAx");
        cubesters.push_back("xaxxxxAxxaxxxxAx");
        cubesters.push_back("xxaxxAxxxxaxxAxx");
        cubesters.push_back("xxxaAxxxxxxaAxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxaAxxxxxxaAxxx");
        cubesters.push_back("xxaxxAxxxxaxxAxx");
        cubesters.push_back("xaxxxxAxxaxxxxAx");
        cubesters.push_back("xaxxxxAxxaxxxxAx");
        cubesters.push_back("xxaxxAxxxxaxxAxx");
        cubesters.push_back("xxxaAxxxxxxaAxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        return cubesters;
    }

    static string getMediumL6N()
    {
        return "Testing for Rakan";
    }

    static vector<string> getMediumL6T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxxxx");
        tile.push_back("x+++++++++++*t*x");
        tile.push_back("x++s+++++++***+x");
        tile.push_back("x+++++++++*+*++x");
        tile.push_back("x+*+++++++*+*++x");
        tile.push_back("x***+++++****t+x");
        tile.push_back("x*t**+++++*++*+x");
        tile.push_back("x***+++++++*+*+x");
        tile.push_back("x******+++++**+x");
        tile.push_back("x+++*++*+++++*+x");
        tile.push_back("x+++*+++*++++++x");
        tile.push_back("x+++*++++*+++++x");
        tile.push_back("x+++*++++*+++++x");
        tile.push_back("x+++*+++++*++++x");
        tile.push_back("x***t******++f+x");
        tile.push_back("xxxxxxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getMediumL6C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxx1xx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxx2xx");
        cubesters.push_back("xx2xxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxx6xxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxx");
        return cubesters;
    }

    static string getHardL1N()
    {
        return "Water T";
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
        return "Remember to Hide";
    }

    static vector<string> getHardL2T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxx");
        tile.push_back("xs+++**++++x");
        tile.push_back("x**********x");
        tile.push_back("xtx+x**x+xtx");
        tile.push_back("x*t******t*x");
        tile.push_back("x*x+x**x+x*x");
        tile.push_back("x****b*****x");
        tile.push_back("x*x+x**x+x*x");
        tile.push_back("x*kx+**+x+dx");
        tile.push_back("x*x+x**x+xdx");
        tile.push_back("xtt*****txfx");
        tile.push_back("xxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getHardL2C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xx+++yu++++x");
        cubesters.push_back("xr++++++++rx");
        cubesters.push_back("xjxxxxxxxxhx");
        cubesters.push_back("xxkxxxxxxkxx");
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxlxxxxxxxlx");
        cubesters.push_back("xxxxxxxxxxxx"); 
        cubesters.push_back("xxxxxxxxxxxx");
        cubesters.push_back("xxxxxyuxxxxx");
        cubesters.push_back("xjixxxxxixhx");
        cubesters.push_back("xxxxxxxxxxxx");
        return cubesters;
    }

    static string getHardL3N()
    {
        return "Dodge, Duck, Dip, Dive, Dodge";
    }

    static vector<string> getHardL3T()
    {
        vector<string> tile;
        tile.push_back("xxxxtxtxtxxxx");
        tile.push_back("xxxxxtbtxtxxx");
        tile.push_back("xxxx*****xxxx");
        tile.push_back("xxxx*****xxxx");
        tile.push_back("tx*********tx");
        tile.push_back("xt*********xt");
        tile.push_back("xs++******ddf");
        tile.push_back("xt*********xt");
        tile.push_back("tx*********tx");
        tile.push_back("xxxx*****xxxx");
        tile.push_back("xxxx*****xxxx");
        tile.push_back("xxxxxtbtxtxxx");
        tile.push_back("xxxxtxtxtxxxx");
        return tile;
    }

    static vector<string> getHardL3C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxhxhxhxxxx");
        cubesters.push_back("xxxxxj+jxjxxx");
        cubesters.push_back("xxxx+++++xxxx");
        cubesters.push_back("xxxx+++++xxxx");
        cubesters.push_back("ix+++++++++ix");
        cubesters.push_back("xk+++++++++xk");
        cubesters.push_back("x++++++++++++");
        cubesters.push_back("xi+++++++++xi");
        cubesters.push_back("kx+++++++++kx");
        cubesters.push_back("xxxx+++++xxxx");
        cubesters.push_back("xxxx+++++xxxx");
        cubesters.push_back("xxxxxj+jxjxxx");
        cubesters.push_back("xxxxhxhxhxxxx");
        return cubesters;
    }

    static string getHardL4N()
    {
        return "Patience is a Virtue";
    }

    static vector<string> getHardL4T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xs*xxxxxxxxxfx");
        tile.push_back("xx**xxxxxxx*+x");
        tile.push_back("xxx**xxxxx**xx");
        tile.push_back("xxxx**xxx**xxx");
        tile.push_back("xxxxx**x**xxxx");
        tile.push_back("xxxxxx***xxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getHardL4C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxyyyyyyyyyyxx");
        cubesters.push_back("xxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxx");
        cubesters.push_back("x++xxxxxxxxx+x");
        cubesters.push_back("xx++xxxxxxx++x");
        cubesters.push_back("xxx++xxxxx++xx");
        cubesters.push_back("xxyx++xxx++xxx");
        cubesters.push_back("xxxyx++x++xyxx");
        cubesters.push_back("xxxxyx+++xyxxx");
        cubesters.push_back("xxxxxyxxxyxxxx");
        cubesters.push_back("xxxxxxyxyxxxxx");
        cubesters.push_back("xxxxxxxyxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxx");
        return cubesters;
    } 

    static string getHardL5N()
    {
        return "Lava Won't Be the Killer";
    }

    static vector<string> getHardL5T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxxx");  
        tile.push_back("xfxxxxxii****+x");
        tile.push_back("xdxk+++ii**vv+x");
        tile.push_back("xdxxxxxii**vv+x");
        tile.push_back("xd************x");
        tile.push_back("x+xxxxxixxxxxxx");
        tile.push_back("xixxxxxixxxxxxx");
        tile.push_back("xixkt*********tx");
        tile.push_back("xixxxxxxxxxxxxx");
        tile.push_back("xillllllll****x");
        tile.push_back("xillllllll**+*x");
        tile.push_back("xillllllll**+*x");
        tile.push_back("xillllllll****x");
        tile.push_back("xst********txkx");
        tile.push_back("xxxxxxxxxxxxxxx");
    
        return tile;
    }

    static vector<string> getHardL5C()
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

    static string getExtremeL1N()
    {
        return "Ice T";
    }

    static vector<string> getExtremeL1T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxx");  //y, q, e, z
        tile.push_back("xiiwiix");
        tile.push_back("xixixix");
        tile.push_back("xwxixwx");
        tile.push_back("xwxixwx");
        tile.push_back("xwxixdx");
        tile.push_back("xsxkxfx");
        return tile;
    }

    static vector<string> getExtremeL1C()
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

    static string getExtremeL2N()
    {
        return "Only Four Extra Steps";
    }

    static vector<string> getExtremeL2T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxx");  //y, q, e, z
        tile.push_back("x++txt+txfx");
        tile.push_back("x+x*x*x*x+x");
        tile.push_back("xtx*x*x*xtx");
        tile.push_back("x+x*x*x*x+x");
        tile.push_back("xtx*x*x*xtx");
        tile.push_back("x+x*x*x*x+x");
        tile.push_back("xtx*x*x*xtx");
        tile.push_back("xpx*x*x*x+x");
        tile.push_back("xsxt+txt++x");
        tile.push_back("xxxxxxxxxxx");
        return tile;
    }

    static vector<string> getExtremeL2C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxx");
        cubesters.push_back("xxxjxhxjxxx"); 
        cubesters.push_back("xxxxxxxxxxx");
        cubesters.push_back("xixxxxxxxix");
        cubesters.push_back("xxxxxxxxxxx");
        cubesters.push_back("xkxxxxxxxkx");
        cubesters.push_back("xxxxxxxxxxx");
        cubesters.push_back("xixxxxxxxix");
        cubesters.push_back("xxxxxxxxxxx");
        cubesters.push_back("xxxjxhxjxxx");
        cubesters.push_back("xxxxxxxxxxx");
        return cubesters;
    }

    static string getExtremeL4N()
    {
        return "Not that Bad";
    }

    static vector<string> getExtremeL4T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxx");
        tile.push_back("xfds*******x");
        tile.push_back("xxxxxxxxxx*x");
        tile.push_back("*****+x****x");
        tile.push_back("*****+x**++x");
        tile.push_back("***xx+x****x");
        tile.push_back("***x*+x****x");
        tile.push_back("**x**xx**xxx");
        tile.push_back("***x*+x****x");
        tile.push_back("x***x+x****x");
        tile.push_back("xb**x++++**x");
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
        return "Timing Matters";
    }

    static vector<string> getExtremeL5T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxxxx");
        tile.push_back("x*bx**++++++*+*x");
        tile.push_back("x**x*xxxxxxxxx*x");
        tile.push_back("x**x+xt+t***tx+x");
        tile.push_back("x**x+x*xxxxx+x*x");
        tile.push_back("xb*x+x*xt**xtx+x");
        tile.push_back("x**x+x*xsxtxtx*x");
        tile.push_back("x**x+x*xxx*x*x*x");
        tile.push_back("x**x+xtxxx*x*x+x");
        tile.push_back("x**xtx***t*x*x*x");
        tile.push_back("x*bx+xxxxxxx*x*x");
        tile.push_back("x**xt****tt+tx+x");
        tile.push_back("x++x+xxxxxxxxx*x");
        tile.push_back("x++++xfddd*++++x");
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
        cubesters.push_back("x++++x+MmMmxxxxx");
        cubesters.push_back("xxxxxxxOxOxxxxxx");
        cubesters.push_back("xxxxxxxMmMmxxxxx");
        return cubesters;
    }

    static string getExtremeL6N()
    {
        return "Glacies Letum";
    }

    static vector<string> getExtremeL6T()
    {
        vector<string> tile;
        tile.push_back("xxxxxxxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxxxxxxx");
        tile.push_back("xiiiixiiiixiiixiibxx");
        tile.push_back("xixiixiixiiixiiixxxx");
        tile.push_back("xiiiiiixiixiiixiiixx");
        tile.push_back("xxiiiixiixxiiixiiixx");
        tile.push_back("xxxxixxixxiixiiixxxx");
        tile.push_back("xxxxiixiiiixixiiiixx");
        tile.push_back("xxxxiixxxxxxxxxxxxxx");
        tile.push_back("xxxiiixxxdiiiiifxxxx");
        tile.push_back("xxxiiiiiidxxxxxxxxxx");
        tile.push_back("xxxxxxxxxixxxxxxxxxx");
        tile.push_back("xiiixixiiixiiixiikxx");
        tile.push_back("xixiiiiixiiixiiixxxx");
        tile.push_back("xiiiiixiiixiiixiiixx");
        tile.push_back("xxiiiixiiixiiixiiixx");
        tile.push_back("xxxxiiiixiiiixiiiiix");
        tile.push_back("xiiiixiiixiiiiixiiix");
        tile.push_back("xsxxxxxxxxxxixxxxxxx");
        tile.push_back("xxxxxxxxxxxxxxxxxxxx");
        return tile;
    }

    static vector<string> getExtremeL6C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxaxxxaxbxxxbxcxxxcx");
        cubesters.push_back("xxrxxxxxxxxxxxxxxxrx");
        cubesters.push_back("xxlxxxxxxxxxxxxxxxlx");
        cubesters.push_back("xxrxxxxxxxxxxxxxxxrx");
        cubesters.push_back("xxaxxxaxbxxxbxcxxxcx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxuxxxyxuxxxuxyxuxxx");
        cubesters.push_back("xaxxxaxoxxxoxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xaxxxaxoxxxoxxxxxxxx");
        cubesters.push_back("xxuxxxyxuxxxuxyxuxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        return cubesters;
    }


    static string getCreditL1N()
    {
        return "Credits";
    }

    static vector<string> getCreditL1T()
    {
        vector<string> tile;
        tile.push_back("7xxxxxxxxxxxxxxxxxxx");
        tile.push_back("xs  CREDIT  PAGE   x");
        tile.push_back("x   CHRISTOPHER J  x");
        tile.push_back("x      KOMPLIN     x");
        tile.push_back("x  PROJECT OUTLINE x");
        tile.push_back("x   LEVEL DESIGN   x");
        tile.push_back("x    ENEMY CODE    x");
        tile.push_back("x    PLAYER CODE   x");
        tile.push_back("x TEXTURE BLENDING x");
        tile.push_back("x    GUI SETUP     x");//10
        tile.push_back("x iiiiiiiiiiiiiiii x");
        tile.push_back("8     YU ZHONG     x");
        tile.push_back("x  CAMERA   MUSIC  x");
        tile.push_back("x   PLAYER  CODE   x");
        tile.push_back("x    TILE  CODE    x");
        tile.push_back("x   LEVEL DESIGN   x");
        tile.push_back("x TEXTURE BLENDING x");
        tile.push_back("x    GUI  SETUP    x");
        tile.push_back("x iiiiiiiiiiiiiiii x");
        tile.push_back("9 RAKAN           fx");

    
        return tile;
    }

    static vector<string> getCreditL1C()
    {
        vector<string> cubesters;
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxx");
        return cubesters;
    }

    static string getCreditL2N()
    {
        return "Enjoy The Credit Page";
    }

    static vector<string> getCreditL2T()
    {
        vector<string> tile;
        tile.push_back("7xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxTxs  CREDIT  PAGE   xTxxxxxxxxx");
        tile.push_back("xxxxxxxxxHxjiiiiiiiiiiiiiiiihxHxxxxxxxxx");
        tile.push_back("xxxxxxxxxAx    CHRISTOPHER  ixAxxxxxxxxx");
        tile.push_back("xxxxxxxxxNxhiiiiiiiiiiiiiiiigxNxxxxxxxxx");
        tile.push_back("xxxxxxxxxKxi     KOMPLIN     xKxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxjiiiiiiiiiiiiiiiihxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxYx PROJECT OUTLINE ixYxxxxxxxxx");
        tile.push_back("xxxxxxxxxOxhiiiiiiiiiiiiiiiigxOxxxxxxxxx");
        tile.push_back("xxxxxxxxxUxi  LEVEL DESIGN   xUxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxjiiiiiiiiiiiiiiiihxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxFx    ENEMY CODE   ixFxxxxxxxxx");
        tile.push_back("xxxxxxxxxOxhiiiiiiiiiiiiiiiigxOxxxxxxxxx");
        tile.push_back("xxxxxxxxxRxi   PLAYER CODE   xRxxxxxxxxx");
        tile.push_back("xxxxxxxxxxxjiiiiiiiiiiiiiiiihxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxPx TEXTURE BLENDINGixPxxxxxxxxx");
        tile.push_back("xxxxxxxxxLxhiiiiiiiiiiiiiiiigxLxxxxxxxxx");
        tile.push_back("xxxxxxxxxAxi   GUI SETUP     xAxxxxxxxxx");
        tile.push_back("xxxxxxxxxYxjiiiiiiiiiiiiiiiihxYxxxxxxxxx");
        tile.push_back("xxxxxxxxxIx    TILE  CODE   ixIxxxxxxxxx");
        tile.push_back("xxxxxxxxxNxhiiiiiiiiiiiiiiiigxNxxxxxxxxx");
        tile.push_back("xxxxxxxxxG8i    YU ZHONG     7G8xxxxxxxx");
        tile.push_back("xxxxxxxxxxxjiiiiiiiiiiiiiiiihxxxxxxxxxxx");
        tile.push_back("xxxxxxxxxHx      CAMERA     ixHxxxxxxxxx");
        tile.push_back("xxxxxxxxxOxhiiiiiiiiiiiiiiiigxOxxxxxxxxx");
        tile.push_back("xxxxxxxxxPxi  PLAYER  CODE   xPxxxxxxxxx");
        tile.push_back("xxxxxxxxxExjiiiiiiiiiiiiiiiihxExxxxxxxxx");
        tile.push_back("xxxxxxxxxxx    TILE  CODE   ixxxxxxxxxxx");
        tile.push_back("xxxxxxxxxYxhiiiiiiiiiiiiiiiigxYxxxxxxxxx");
        tile.push_back("xxxxxxxxxOxi  LEVEL DESIGN   xOxxxxxxxxx");
        tile.push_back("xxxxxxxxxUxjiiiiiiiiiiiiiiiihxUxxxxxxxxx");
        tile.push_back("xxxxxxxxxxx TEXTURE BLENDINGixxxxxxxxxxx");
        tile.push_back("xxxxxxxxxExhiiiiiiiiiiiiiiiigxExxxxxxxxx");
        tile.push_back("xxxxxxxxxNxi   GUI  SETUP    xNxxxxxxxxx");
        tile.push_back("xxxxxxxxxJxjiiiiiiiiiiiiiiiihxJxxxxxxxxx");
        tile.push_back("xxxxxxxxxOx      MUSIC      ixOxxxxxxxxx");
        tile.push_back("xxxxxxxxxYxhiiiiiiiiiiiiiiiigxYxxxxxxxxx");
        tile.push_back("xxxxxxxxxExiTHIS CREDIT PAGE xExxxxxxxxx");
        tile.push_back("xxxxxxxxxDxjiiiiiiiiiiiiiiiihxDxxxxxxxxx");
        tile.push_back("9xxxxxxxxxxRAKAN ONE CUBESTERfxxxxxxxxxx");
        return tile;
    }
    static vector<string> getCreditL2C()
    {
        vector<string> cubesters;
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
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
        cubesters.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
        return cubesters;
    }

};