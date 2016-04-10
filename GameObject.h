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

class Simulator;
class Ball;

class GameObject
{
public:
	Ogre::SceneManager* sceneMgr;
	Simulator* simulator;
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
	Simulator* sim,
	Ogre::SceneNode* node,
	btScalar m);
	virtual ~GameObject();
	btRigidBody* getBody();
};

class Player : public GameObject
{
public:
	Ogre::Vector3 position;
	Ball* playerBall;
	Ogre::Real points;

public:
	Player(Ogre::String n,
	Ogre::SceneManager* mgr,
	Simulator* sim,
	Ogre::SceneNode* node,
	btScalar m, 
	Ball* ball,
	Ogre::Vector3 pos = Ogre::Vector3(0.0, 0.0, 0.0),
	Ogre::Real score = 0);
	virtual ~Player();
	void create(Ogre::Degree p = Ogre::Degree(90), Ogre::Degree = Ogre::Degree(180), Ogre::Degree = Ogre::Degree(0));
	void scored();
};

class Ball : public GameObject
{
public:
	Ogre::Vector3 position;

public:
	Ball(Ogre::String n,
	Ogre::SceneManager* mgr,
	Simulator* sim,
	Ogre::SceneNode* node,
	btScalar m, Ogre::Vector3 pos = Ogre::Vector3(0.0, 0.0, 0.0));
	virtual ~Ball();
	void create();
	void kickBall(btScalar power, btScalar angle, btScalar height);
	void setGhostBallPos(float x, float y, float z);

};

class GhostBall : public Ball
{
public:
	GhostBall(Ogre::String n,
	Ogre::SceneManager* mgr,
	Simulator* sim,
	Ogre::SceneNode* node,
	btScalar m, Ogre::Vector3 pos = Ogre::Vector3(0.0, 0.0, 0.0));
	virtual ~GhostBall();
	void create();
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
	Simulator* sim,
	Ogre::SceneNode* node,
	btScalar m, double x, double y, Ogre::Vector3 norm, int dist);
	virtual ~Wall();
	virtual void create();

};

class Goal : public Wall
{
private:
	double xTrans;
	double yTrans;
public:
	Goal(Ogre::String n,
	Ogre::SceneManager* mgr,
	Simulator* sim,
	Ogre::SceneNode* node,
	btScalar m, double x, double y, Ogre::Vector3 norm, int dist);
	virtual ~Goal();
	virtual void create();
	virtual bool ballScored(Ogre::Vector3 pos);

};


class Simulator {
protected:
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	std::deque<GameObject*> objList;
public:
	Simulator();
	~Simulator();
	void addObject(GameObject* o);
	bool removeObject(GameObject* o);
	bool stepSimulation(bool scored, const Ogre::Real elapsedTime, Mix_Music* music,
	int maxSubSteps = 1, const Ogre::Real fixedTimestep = 1.0f/60.0f);
	btDiscreteDynamicsWorld* getDynamicsWorld();
	void kickBall(btScalar power, btScalar angle, btScalar height);
	void destroyNode(Ogre::SceneNode* node);
	Ball* reload();

};
#endif // #ifndef __GameObject_h_
