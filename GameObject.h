#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <string>
#include <iostream>
#include <OgreMeshManager.h>
#include <btBulletDynamicsCommon.h>
#include <OgreSubMesh.h>
#include <OgreMath.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <vector>

class GameObject
{
public:
	Ogre::SceneManager* sceneMgr;
	Ogre::SceneNode* rootNode;
	Ogre::Entity* geom;
	btCollisionShape* shape;
	btScalar mass;
	btRigidBody* body;
	btTransform tr;
	btVector3 inertia;
	btDefaultMotionState* motionState;	

public:
	Ogre::String name;

	GameObject(Ogre::String n,
	Ogre::SceneManager* mgr,
	Ogre::SceneNode* node,
	btScalar m);
	virtual ~GameObject();
	btRigidBody* getBody();
};

class Player : public GameObject
{
public:
	Ogre::Vector3 position;
	int playerX;
	int playerY;
	Ogre::Vector3 startPosition;
	double health;
	bool poison;
	int burn;
	int oxygen;
	int key;
	static double length() { return 50; }
	static double burnDamage(){return 5;}
	static double poisonDamage(){return 2;}
	static double spikeDamage(){return 39;}
	//movement information
	static double moveSpeed() { return 170; } //raise to 150ish
	void setBackPlayer();
	Ogre::Vector3 endPos;
	int startPlayerX;
	int startPlayerY;
	int direction;
	bool inMotion;
	bool levelFinished;
public:
	Player(Ogre::String n,
	Ogre::SceneManager* mgr,
	Ogre::SceneNode* node,
	btScalar m,
	Ogre::Vector3 pos = Ogre::Vector3(0.0, 0.0, 0.0));
	virtual ~Player();
	void create(Ogre::Degree p = Ogre::Degree(90), Ogre::Degree = Ogre::Degree(180), Ogre::Degree = Ogre::Degree(0));
	bool move(int dir, Ogre::Vector3 p);
	bool simulate(const Ogre::Real elapsedTime);
	bool canMove();
	void gotKey();
	bool usedKey();
	bool hasKey();
	int getPlayerX();
	int getPlayerY();
	void setPlayerCord(int xI, int yI, int legthTile, double xCord, double zCord);
	void changeMaterial(std::string s);
	void removeBurn();
	void updateStatus();
	void damageTaken(double damage);
	void oxygenLost(int amount);
	void breath();
	void kill();
	bool isAlive();
	void respawn();

};



class Wall : public GameObject
{
protected:
	double xLength;
	double yLength;
	Ogre::Vector3 normal;
	int distFromCenter;
public:
	Wall(Ogre::String n,
	Ogre::SceneManager* mgr,
	Ogre::SceneNode* node,
	btScalar m, double x, double y, Ogre::Vector3 norm, int dist);
	virtual ~Wall();
	virtual void create();

};

	// void destroyNode(Ogre::SceneNode* node);
	// void reload();

#endif // #ifndef __GameObject_h_
