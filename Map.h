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

	//player
		//goingUp = true;
		//right/left/down -- for the noobs to know what other 3 i was talking about
	//  "aaFaaaa" 
	//  "aabaaaa"
	//  "aabaaaa"
	//  "lllllaa"
	//  "aabaaaa"
	//  "aapaaaa"
	//  "aaSaaaa"


public:
	Map(Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos, std::vector< std::vector<Tile *> >);
	Map(Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos, std::vector< std::string >);
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