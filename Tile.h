
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
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
	Ogre::Entity* ent;
	AbstractTile *up;
	AbstractTile *right;
	AbstractTile *left;
	AbstractTile *down;
	int mode;
	Mix_Music* damageSound;
public:
	static double length() { return 50; }   //cosnt length for all tiles
	virtual bool getIsWalkable(Player *p);
	virtual Ogre::Vector3 getPosition();
	virtual void create(std::string material) = 0; 				//cant call
	virtual ~AbstractTile() {} 				//does nothing
	virtual void event(Player* p) = 0;
	virtual void reload();
	void setNeighbors(AbstractTile *u, AbstractTile *r, AbstractTile *d, AbstractTile *l);
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

class BloodPathTile : public PathTile
{
public:
	BloodPathTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~BloodPathTile();
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
class SpikeTile : public PathTile
{
public:
	SpikeTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~SpikeTile();
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

class DDownTile : public PathTile
{
public:
	DDownTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~DDownTile();
	virtual void event(Player* p);
	
};

class DUpTile : public PathTile
{
public:
	DUpTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~DUpTile();
	virtual void event(Player* p);
	
};

class DLeftTile : public PathTile
{
public:
	DLeftTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~DLeftTile();
	virtual void event(Player* p);
	
};

class DRightTile : public PathTile
{
public:
	DRightTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~DRightTile();
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
	bool unlocked;
	DoorTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~DoorTile();
	virtual void event(Player* p);
	virtual void reload();
	virtual bool getIsWalkable(Player *p);
	
};

//Key tile
class KeyTile : public PathTile
{
public:
	bool takenKey;
	KeyTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~KeyTile();
	virtual void reload();
	virtual void event(Player* p);
	
};

class BloodKeyTile : public KeyTile
{
public:
	BloodKeyTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~BloodKeyTile();
	virtual void reload();
	virtual void event(Player* p);
};

class RakanTile : public PathTile
{
public:
	RakanTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~RakanTile();
	virtual void event(Player* p);
	
};

class SpaceTile : public PathTile
{
public:
	SpaceTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~SpaceTile();
	virtual void event(Player* p);
	
};

class CureTile : public PathTile
{
public:
	CureTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~CureTile();
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

class LetterTile : public PathTile
{
public:
	LetterTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd);
	virtual ~LetterTile();
};

// wrapper class
class Tile
{
protected:
	AbstractTile *tile;
public:
	Tile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, char t, int mode);
	~Tile();
	void create(std::string material);
	double    length() { return AbstractTile::length(); }
	bool getIsWalkable(Player *p);
	Ogre::Vector3 getPosition();

    void event(Player* p);
    void reload();
    void setNeighbors(Tile *u, Tile *r, Tile *d, Tile *l);

	static char typeForPathTile() { return '+'; }
	static char typeForBloodPathTile() { return '*'; }
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
	static char typeForKeyTile() {return 'k';}
	static char typeForBloodKeyTile() {return 'b';}
	static char typeForRakanTile() { return 'r'; }
	static char typeForSpikeTile() { return 'v'; }
	static char typeForCureTile() {return 'c';}
	static char typeForSpaceTile() {return ' ';}
	//key for directional tiel 
	//y for up, h for down, g for left and j for right
	static char typeForDUpTile() {return 'y';}
	static char typeForDDownTile() {return 'h';}
	static char typeForDLeftTile() {return 'g';}
	static char typeForDRightTile() {return 'j';}

	static char typeForATile() {return 'A';}
	static char typeForZTile() {return 'Z';}

};

