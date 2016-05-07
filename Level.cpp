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
	// loading screen
	if(levelCat == 0)
	{
		if(levelN == 0)
		{
			tileMap     = getLoadingLevelT();
			cubesterMap = getLoadingLevelC();
			name = "";

		}
	}
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
		else if(levelN == 6)
		{
			tileMap     = getIntroL6T();
			cubesterMap = getIntroL6C();
			name        = getIntroL6N();
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
		else if(levelN ==2)
		{
			tileMap     = getMediumL2T();
			cubesterMap = getMediumL2C();
			name        = getMediumL2N();
		}
		else if(levelN == 3)
		{
			tileMap     = getMediumL3T();
			cubesterMap = getMediumL3C();
			name        = getMediumL3N();
		}
		else if(levelN == 4)
		{
			tileMap     = getMediumL4T();
			cubesterMap = getMediumL4C();
			name        = getMediumL4N();
		}
		else if(levelN == 5)
		{
			tileMap     = getMediumL5T();
			cubesterMap = getMediumL5C();
			name        = getMediumL5N();
		}
		else if(levelN == 6)
		{
			tileMap     = getMediumL6T();
			cubesterMap = getMediumL6C();
			name        = getMediumL6N();
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
		else if(levelN == 2)
		{
			tileMap     = getHardL2T();
			cubesterMap = getHardL2C();
			name        = getHardL2N();
		}
		else if(levelN == 3)
		{
			tileMap     = getHardL3T();
			cubesterMap = getHardL3C();
			name        = getHardL3N();
		}
		else if(levelN == 4)
		{
			tileMap     = getHardL4T();
			cubesterMap = getHardL4C();
			name        = getHardL4N();
		}
		else if(levelN == 5)
		{
			tileMap     = getHardL5T();
			cubesterMap = getHardL5C();
			name        = getHardL5N();
		}
	}
	else if(levelCat == 4)
	{
		if(levelN == 1)
		{
			tileMap     = getExtremeL1T();
			cubesterMap = getExtremeL1C();
			name        = getExtremeL1N();
		}
		else if(levelN == 2)
		{
			tileMap     = getExtremeL2T();
			cubesterMap = getExtremeL2C();
			name        = getExtremeL2N();
		}
		else if(levelN == 3)
		{
			tileMap     = getExtremeL4T();
			cubesterMap = getExtremeL4C();
			name        = getExtremeL4N();
		}
		else if(levelN == 4)
		{
			tileMap     = getExtremeL5T();
			cubesterMap = getExtremeL5C();
			name        = getExtremeL5N();
		}
		else if(levelN == 5)
		{
			tileMap     = getExtremeL6T();
			cubesterMap = getExtremeL6C();
			name        = getExtremeL6N();
		}
	}
	else if(levelCat == 5)
	{
		// if(levelN == 1)
		// {
		// 	tileMap     = getCreditL1T();
		// 	cubesterMap = getCreditL1C();
		// 	name        = getCreditL1N();
		// }
		if(levelN == 1)
		{
			tileMap     = getCreditL2T();
			cubesterMap = getCreditL2C();
			name        = getCreditL2N();
		}
	}
}

