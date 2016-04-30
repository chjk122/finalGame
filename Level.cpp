#include "Level.h"

Level::Level(int levelCat, int levelN)
{
	setMaps(levelCat, levelN);
}

Level::~Level() {}

vector<string> Level::getTileMap()
{
	return tileMap;
}
vector<string> Level::getCubesterMap()
{
	return cubesterMap;
}

string Level::getName()
{
	return name;
}

void Level::setMaps(int levelCat, int levelN)
{
	//intro levels
	if(levelCat == 1)
	{	
		if(levelN == 1)
		{
			tileMap     = getIntroL1T();
			cubesterMap = getIntroL1C();
			name        = getIntroL1N();
		}
		else if(levelN == 2)
		{
			tileMap     = getIntroL2T();
			cubesterMap = getIntroL2C();
			name        = getIntroL2N();
		}
		else if(levelN == 3)
		{
			tileMap     = getIntroL3T();
			cubesterMap = getIntroL3C();
			name        = getIntroL3N();
		}
		else if(levelN == 4)
		{
			tileMap     = getIntroL4T();
			cubesterMap = getIntroL4C();
			name        = getIntroL4N();
		}
		else if(levelN == 5)
		{
			tileMap     = getIntroL5T();
			cubesterMap = getIntroL5C();
			name        = getIntroL5N();
		}
	}
	else if(levelCat == 2)
	{
		if(levelN == 1)
		{
			tileMap     = getMediumL1T();
			cubesterMap = getMediumL1C();
			name        = getMediumL1N();
		}
	}
	else if(levelCat == 3)
	{
		if(levelN == 1)
		{
			tileMap     = getHardL1T();
			cubesterMap = getHardL1C();
			name        = getHardL1N();
		}
	}
}