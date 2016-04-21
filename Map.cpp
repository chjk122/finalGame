#include "Map.h"

Map::Map(Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos, std::vector< std::vector<Tile *> > v)
{
	
}

Map::Map(Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos, std::vector< std::string > v):
mgr(sceneMgr)
{
	std::string name;
	Tile *temp;
	Ogre::Vector3 pos(centerOfTopleftTilePos.x, centerOfTopleftTilePos.y, centerOfTopleftTilePos.z);
	for(int x = 0; x < v.size(); x++)
	{
		map.push_back(std::vector<Tile *>());
		for(int y = 0; y < v.size(); y++)
		{
			name = x + "y" + y;
			temp = new Tile(mgr,pos, x, y, v[x][y]);
			map[x].push_back(temp);
			pos.x = pos.x + AbstractTile::length(); // + length to the right in 2d
		}
		pos.z = pos.z + AbstractTile::length(); // + length downward in 2d
		pos.x = centerOfTopleftTilePos.x; // reset the x 
	}
}

Map::~Map()
{
	for(int x = 0; x < getLength(); x++)
	{
		for(int y = 0; y < getLength(); y++)
		{
			delete map[x][y];
		}
		map[x].clear();
	}
	map.clear();

}

int Map::getLength()
{
	return map.size();
}

bool Map::move(int direction)
{
	int nextX = player->getPlayerX();
	int nextY = player->getPlayerY();
	if(direction == 0)      // up
	{
		nextX--;
	}
	else if(direction == 1) // right
	{
		nextY++;
	}
	else if(direction == 2) // down
	{
		nextX++;
	}
	else if(direction == 3) // left
	{
		nextY--;
	}

	if(canMove(nextX, nextY, direction) && player->move(direction))
		return true;
	else
		return false;
}

bool Map::canMove(int tileX, int tileY, int direction)
{
	if(tileX < 0 || tileY < 0 || tileX >= getLength() || tileY >= getLength()) //case: out of bounds
		return false;

	if(map[tileX][tileY]->getIsWalkable())
	{
		return true; //exists and is walkable
	}
	else //tile is not walkabe
	{
		return false;
	}
}

void Map::simulate()
{
	//loop through enemy/player and call thier simulate method
}
