#ifndef Map_H
#define Map_H

#include "GameObject.h"
#include <vector>

class Map
{
protected:
	std::vector<vector<Tile>> map;
	int size;
public:
	Map(int size);
	virtual ~Map();
	void addTile(Tile t);
	std::vector<Tile> getTileMap();

};



#endif // #ifndef __Map_h_