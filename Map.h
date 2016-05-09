#ifndef Map_H
#define Map_H

#include "GameObject.h"
#include "Cubester.h"
#include "Tile.h"
#include "Level.h"
#include <vector>
#include <string>
#include <iostream>
#include <ctype.h>

class Map
{
protected:
	std::vector< std::vector<Tile *> > map;
	std::vector< Cubester *> cubesters;
	Player *player;
	Ogre::SceneManager* mgr;
	std::string name;
	//items


public:
	Map(Player *play, Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos, std::vector< std::string > v, std::vector< std::string > e);
	Map(Player *play, Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos, int catNum, int levNum);
	virtual ~Map();

	int getLength();
	// int getNumCubesters();
	// Player *getPlayer();
	bool move(int direction);
	void simulate(const Ogre::Real elapsedTime);
	void destroyNode(Ogre::SceneNode* node);
	void destoryAllSceneNodes();
	void parseMaps(Ogre::Vector3 centerOfTopleftTilePos,
		 	   std::vector< std::string > v, std::vector< std::string > e);
	std::string getName();
	bool isPlayerAlive();
	void respawn();

private:
	bool canMove(int tileX, int tileY, int direction);

};



#endif // #ifndef __Map_h_