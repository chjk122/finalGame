
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <string>
#include <sstream>
#include <iostream>
#include <OgreMeshManager.h>
#include <btBulletDynamicsCommon.h>
#include <OgreSubMesh.h>
#include "GameObject.h"
#include <OgreMath.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class AbstractTile
{
protected:
	Ogre::Vector3 position;
	Ogre::SceneManager* mgr;
	int xIndex;
	int yIndex;
	bool isWalkable;
public:
	static double length() { return 50; }   //cosnt length for all tiles
	virtual bool getIsWalkable(); 			//for children to all have
	virtual Ogre::Vector3 getPosition();
	virtual void create(std::string material) = 0; 				//cant call
	virtual ~AbstractTile() {} 				//does nothing
	virtual void event(Player* p) = 0;
};

// basic walkable tile 
class PathTile : public AbstractTile
{
public:
	PathTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~PathTile();
	virtual void create(std::string material);
	virtual void event(Player* p);

};

// start tile
class StartTile : public PathTile
{
public:
	StartTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~StartTile();
	

};
//finish tile
class FinishTile : public PathTile
{
public:
	FinishTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~FinishTile();
	virtual void event(Player* p);

};
//Lava tile
class LavaTile : public PathTile
{
public:
	LavaTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~LavaTile();
	virtual void event(Player* p);
	
};

//Poison tile
class PoisonTile : public PathTile
{
public:
	PoisonTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~PoisonTile();
	virtual void event(Player* p);
	
};

//Ice tile
class IceTile : public PathTile
{
public:
	IceTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~IceTile();
	virtual void event(Player* p);
	
};

//Water tile
class WaterTile : public PathTile
{
public:
	WaterTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~WaterTile();
	virtual void event(Player* p);
	
};

//Teleport tile
class TeleportTile : public PathTile
{
public:
	TeleportTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~TeleportTile();
	virtual void event(Player* p);
	
};

//Slow tile
class SlowTile : public PathTile
{
public:
	SlowTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~SlowTile();
	virtual void event(Player* p);
	
};

//Door tile
class DoorTile : public PathTile
{
public:
	DoorTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~DoorTile();
	virtual void event(Player* p);
	
};

class RakanTile : public PathTile
{
public:
	RakanTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~RakanTile();
	virtual void event(Player* p);
	
};

// basic nonwalkable tile
class OuterTile : public PathTile
{
public:
	OuterTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~OuterTile();
	virtual void event(Player* p);
};

// wrapper class
class Tile
{
protected:
	AbstractTile *tile;
public:
	Tile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, char t);
	~Tile();
	void create(std::string material);
	double length() { return AbstractTile::length(); }
	bool getIsWalkable();
	Ogre::Vector3 getPosition();
    void event(Player* p);

	static char typeForPathTile() { return '+'; }
	static char typeForOuterTile() { return 'x'; }
	static char typeForStartTile() { return 's'; }
	static char typeForFinishTile() { return 'f'; }
	static char typeForLavaTile() { return 'l'; }
	static char typeForIceTile() { return 'i'; }
	static char typeForWaterTile() { return 'w'; }
	static char typeForPoisonTile() { return 'p'; }
	static char typeForTeleportTile() { return 't'; }
	static char typeForSlowTile() { return 'o'; }
	static char typeForDoorTile() {return 'd';}
	static char typeForRakanTile() { return 'r'; }

};

