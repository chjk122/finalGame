#include "Map.h"

Map::Map(int size)
{
	
}

Map::~Map()
{

}

void Map::addTile(Tile t)
{
	map.push_back(t);
}

std::vector<Tile> Map::getTileMap()
{
	return map;
}