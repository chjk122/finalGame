#ifndef Map_H
#define Map_H

#include "GameObject.h"
#include "Tile.h"
#include <vector>
#include <string>
#include <iostream>

class Map
{
protected:
	std::vector< std::vector<Tile *> > map;
	std::vector< Cubester *> cubesters;
	Player *player;
	Simulator *sim;
	Ogre::SceneManager* mgr;
	//items


public:
	Map(Player *play, Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos, std::vector< std::vector<Tile *> >);
	Map(Player *play, Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos, std::vector< std::string >);
	virtual ~Map();

	int getLength();
	// int getNumCubesters();
	// Player *getPlayer();
	bool move(int direction);
	void simulate();

private:
	bool canMove(int tileX, int tileY, int direction);

};



#endif // #ifndef __Map_h_