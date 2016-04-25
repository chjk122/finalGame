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
	static double moveSpeed() { return 200; } //raise to 150ish
	Ogre::Vector3 endPos;
	int direction;
	int pathLength;
	Ogre::Vector3 position;
	std::string name;
	Ogre::SceneManager* mgr;
	Ogre::SceneNode* rootNode;
	int xIndex;
	int yIndex;
	Ogre::Entity* ent;
	bool inMotion;
	int actionIndex;
public:
	static double length() { return 50; } 
	virtual Ogre::Vector3 getPosition();
	virtual void create(std::string material); 				//cant call
	virtual ~AbstractCubester() {} 				//does nothing

	virtual void simulate(const Ogre::Real elapsedTime);
	virtual int getAction();
	virtual int getX();
	virtual int getY();
	virtual int goUp();
	virtual int goRight();
	virtual int goDown();
	virtual int goLeft();
};

// basic walkable tile 
class CubesterTLSquare : public AbstractCubester
{
public:
	CubesterTLSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterTLSquare();
	virtual int getAction();
};

class CubesterTRSquare : public AbstractCubester
{
public:
	CubesterTRSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterTRSquare();
	virtual int getAction();
};

class CubesterBRSquare : public AbstractCubester
{
public:
	CubesterBRSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterBRSquare();
	virtual int getAction();
};

class CubesterBLSquare : public AbstractCubester
{
public:
	CubesterBLSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length);
	virtual ~CubesterBLSquare();
	virtual int getAction();
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

	void simulate(const Ogre::Real elapsedTime);
	int getX();
	int getY();

	static char typeForCubesterTLSquare() { return 'a'; }
	static char typeForCubesterTRSquare() { return 'b'; }
	static char typeForCubesterBRSquare() { return 'c'; }
	static char typeForCubesterBLSquare() { return 'd'; }

};