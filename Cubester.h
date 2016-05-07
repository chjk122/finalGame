#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <string>
#include <sstream>
#include <iostream>
#include <OgreMeshManager.h>
#include <btBulletDynamicsCommon.h>
#include <OgreSubMesh.h>
#include <OgreMath.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class AbstractCubester
{
protected:
	//movement information
	virtual double moveSpeed(); //raise to 150ish
	Ogre::Vector3 endPos;
	int direction;
	int pathLength;
	Ogre::Vector3 position;
	std::string name;
	Ogre::SceneManager* mgr;
	Ogre::SceneNode* rootNode;
	Ogre::Entity* ent;
	bool inMotion;
	int actionIndex;
	Ogre::Vector3 startPosition;
public:
	static double length() { return 50; } 
	virtual Ogre::Vector3 getPosition();
	virtual void create(std::string material); 				//cant call
	virtual ~AbstractCubester() {} 				//does nothing
	virtual Ogre::SceneNode * getNode();
	virtual std::string getName();
	virtual void simulate(const Ogre::Real elapsedTime, Ogre::Vector3 playerPos);
	virtual void reload();
	virtual int getAction(Ogre::Vector3 playerPos);
	virtual int goUp();
	virtual int goRight();
	virtual int goDown();
	virtual int goLeft();
	virtual int move(int dir);
};

// basic walkable tile 
//*-------------------------------------Square Cubester-----------------------------*//
class CubesterTLSquare : public AbstractCubester
{
public:
	CubesterTLSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterTLSquare();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterTRSquare : public AbstractCubester
{
public:
	CubesterTRSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterTRSquare();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterBRSquare : public AbstractCubester
{
public:
	CubesterBRSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterBRSquare();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterBLSquare : public AbstractCubester
{
public:
	CubesterBLSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterBLSquare();
	virtual int getAction(Ogre::Vector3 playerPos);
};
//*-------------------------------------CounterClockwise Square Cubester-----------------------------*//
class CubesterCCTLSquare : public AbstractCubester
{
public:
	CubesterCCTLSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterCCTLSquare();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterCCTRSquare : public AbstractCubester
{
public:
	CubesterCCTRSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterCCTRSquare();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterCCBRSquare : public AbstractCubester
{
public:
	CubesterCCBRSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterCCBRSquare();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterCCBLSquare : public AbstractCubester
{
public:
	CubesterCCBLSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterCCBLSquare();
	virtual int getAction(Ogre::Vector3 playerPos);
};
//*-------------------------------------Line Cubester-----------------------------*//
class CubesterTBLine : public AbstractCubester
{
public:
	CubesterTBLine(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterTBLine();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterBTLine : public AbstractCubester
{
public:
	CubesterBTLine(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterBTLine();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterLRLine : public AbstractCubester
{
public:
	CubesterLRLine(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterLRLine();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterRLLine : public AbstractCubester
{
public:
	CubesterRLLine(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterRLLine();
	virtual int getAction(Ogre::Vector3 playerPos);
};

//*-------------------------------------Teleport Cubester-----------------------------*//
class CubesterTTP : public AbstractCubester
{
public:
	CubesterTTP(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterTTP();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterBTP : public AbstractCubester
{
public:
	CubesterBTP(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterBTP();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterRTP : public AbstractCubester
{
public:
	CubesterRTP(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterRTP();
	virtual int getAction(Ogre::Vector3 playerPos);
};

class CubesterLTP : public AbstractCubester
{
public:
	CubesterLTP(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterLTP();
	virtual int getAction(Ogre::Vector3 playerPos);
};

//*-------------------------------------------Smart Cubester---------------------------*//
class CubesterChase : public AbstractCubester
{
public:
	CubesterChase(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int distance);
	virtual ~CubesterChase();
	virtual int getAction(Ogre::Vector3 playerPos);
	int moveTowardsPos(Ogre::Vector3 position);

};

// wrapper class
class Cubester
{
protected:
	AbstractCubester *cubester;
public:
	Cubester(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length, char t);
	Ogre::Vector3 getPosition();
	void create(std::string material);
	~Cubester();

	void simulate(const Ogre::Real elapsedTime, Ogre::Vector3 playerPos);
	Ogre::SceneNode * getNode();
	std::string getName();
	void reload();
	int getX();
	int getY();

	static char typeForCubesterTLSquare() { return 'a'; }
	static char typeForCubesterTRSquare() { return 'b'; }
	static char typeForCubesterBRSquare() { return 'c'; }
	static char typeForCubesterBLSquare() { return 'd'; }
	static char typeForCubesterCCTLSquare() { return 'm'; }
	static char typeForCubesterCCTRSquare() { return 'n'; }
	static char typeForCubesterCCBRSquare() { return 'o'; }
	static char typeForCubesterCCBLSquare() { return 'p'; }
	static char typeForCubesterTBLine() { return 'y'; }
	static char typeForCubesterBTLine() { return 'u'; }
	static char typeForCubesterLRLine() { return 'l'; }
	static char typeForCubesterRLLine() { return 'r'; }
	static char typeForCubesterBTP() { return 'h'; } //starts bot goes up
	static char typeForCubesterLTP() { return 'i'; } //starts leftside goes down
	static char typeForCubesterTTP() { return 'j'; } //starts top goes down
	static char typeForCubesterRTP() { return 'k'; } //starts rightside goes left
	static char typeForCubesterChase() { return 'z';}
};