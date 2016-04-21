#include "GameObject.h"

GameObject::GameObject(Ogre::String n,
	Ogre::SceneManager* mgr,
	Simulator* sim,
	Ogre::SceneNode* node,
	btScalar m) : 
	name(n), sceneMgr(mgr), simulator(sim), rootNode(node), mass(m)
{
	
}

GameObject::~GameObject()
{
	simulator->removeObject(this);
	delete shape;
	delete motionState;
	delete body;
}
btRigidBody* GameObject::getBody()
{
	return body;
}

Player::Player(Ogre::String n,
	Ogre::SceneManager* mgr,
	Simulator* sim,
	Ogre::SceneNode* node,
	btScalar m,
	Ogre::Vector3 pos) :
	GameObject(n,mgr,sim,node,m),
	position(pos)
{
	inertia = btVector3(0,0,0);
}

Player::~Player()
{
}

void Player::create(Ogre::Degree p, Ogre::Degree r, Ogre::Degree y)
{
	Ogre::MeshManager::getSingleton().create("outfit_soccer_player_shirt1.001.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::Entity* entity = sceneMgr->createEntity(Ogre::MeshManager::getSingleton().getByName(
		"outfit_soccer_player_shirt1.001.mesh", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));

    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name, position);
    rootNode->attachObject(entity);
    rootNode->setScale(60, 60, 60);
    rootNode->pitch(Ogre::Degree(p));
    rootNode->roll(Ogre::Degree(r));
}

bool Player::move(int direction)
{
    if(canMove())
    {
        //execute move code
        return false;
    }
    else
        return false;
}

bool Player::canMove()
{
    //if player not in motion and is alive return true
    return false;
}

int Player::getPlayerX()
{
    return playerX;
}
int Player::getPlayerY()
{
    return playerY;
}   

Wall::Wall(Ogre::String n,
    Ogre::SceneManager* mgr,
    Simulator* sim,
    Ogre::SceneNode* node,
    btScalar m, double x, double y, Ogre::Vector3 norm, int dist):
    GameObject(n,mgr,sim,node,m),
    xLength(x), yLength(y), normal(norm), distFromCenter(dist)
{

}
Wall::~Wall()
{

}

void Wall::create()
{
    Ogre::Plane plane(normal, distFromCenter);

    Ogre::Vector3 up;
    if(normal == Ogre::Vector3::UNIT_Y ||normal == Ogre::Vector3::NEGATIVE_UNIT_Y)
    {
        up = Ogre::Vector3::UNIT_Z;
    }
    else
    { 
        (up = Ogre::Vector3::UNIT_Y);
    }
    Ogre::MeshManager::getSingleton().createPlane(name, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
        xLength,yLength,20,20,true,1,5,5,up);

    btTransform groundTransform;
    groundTransform.setIdentity();
    // if(norm.x < 0 || norm.y < 0 || norm.z < 0)  //roof, posZ, posX
    //     groundTransform.setOrigin(btVector3((distFromCenter*norm.x)+(5*norm.x), (distFromCenter*norm.y) - (5*norm.y) + 5, (distFromCenter*norm.z) - (norm.z *5)));
    // else
        groundTransform.setOrigin(btVector3((distFromCenter*normal.x)-(10*normal.x), (distFromCenter*normal.y) - (10*normal.y), (distFromCenter*normal.z) - (normal.z *10)));
    inertia = btVector3(0,0,0);

    btScalar x1(250.);
    btScalar y1(250.);
    btScalar z1(250.);

    if(normal.x != 0){
        x1 = 10.;
    }
    else if(normal.y != 0){
        y1 = 10.;
    }
    else if(normal.z != 0) {
        z1 = 10.;
    }

    shape = new btBoxShape(btVector3(x1, y1, z1));
    motionState = new btDefaultMotionState(groundTransform);
    shape->calculateLocalInertia(mass, inertia);

    btRigidBody::btRigidBodyConstructionInfo groundRBInfo(mass, motionState, shape, inertia);
    body = new btRigidBody(groundRBInfo);
    body->setRestitution(.5);
    body->setFriction(50.0);
    body->setRollingFriction(20.3f);


    simulator->addObject(this);
	Ogre::Entity* entity = sceneMgr->createEntity(name); 
    sceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entity); 
    entity->setMaterialName("Examples/Rocky"); 
    entity->setCastShadows(false);
}

/*-----------------------------Start of Cubester-----------------------------*/
Cubester::Cubester(Ogre::String n,
    Ogre::SceneManager* mgr,
    Simulator* sim,
    Ogre::SceneNode* node,
    btScalar m,
    Ogre::Vector3 pos) :
    GameObject(n,mgr,sim,node,m),
    position(pos)
{
    inertia = btVector3(0,0,0);
}

Cubester::~Cubester()
{
}

void Cubester::create(/*Ogre::Degree p, Ogre::Degree r, Ogre::Degree y*/)
{
    // Ogre::MeshManager::getSingleton().create("outfit_soccer_player_shirt1.001.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    // Ogre::Entity* entity = sceneMgr->createEntity(Ogre::MeshManager::getSingleton().getByName(
    //     "outfit_soccer_player_shirt1.001.mesh", 
    //     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));

    // rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name, position);
    // rootNode->attachObject(entity);
    // rootNode->setScale(60, 60, 60);
    // rootNode->pitch(Ogre::Degree(p));
    // rootNode->roll(Ogre::Degree(r));
}






Simulator::Simulator()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
	overlappingPairCache,
	solver,
	collisionConfiguration);
	// dynamicsWorld->setGravity(btVector3(0.0, -0.098, 0.0));
	// dynamicsWorld->setGravity(btVector3(0.0, -98., 0.0));
    dynamicsWorld->setGravity(btVector3(0.0, 0.0, 0.0));
	objList = std::deque<GameObject*>();
	//Add collision shapes to reuse among rigid bodies
}

Simulator::~Simulator()
{
	for (std::deque<GameObject*>::iterator it = objList.begin(); it!=objList.end(); ++it)
	{
		delete *it;
	}
	delete collisionConfiguration;
	delete dispatcher;
	delete overlappingPairCache;
	delete solver;
	delete dynamicsWorld;
}
void Simulator::addObject (GameObject* o)
{
	objList.push_back(o);
	dynamicsWorld->addRigidBody(o->getBody());
}

bool Simulator::removeObject (GameObject* o)
{
	for (std::deque<GameObject*>::iterator it = objList.begin(); it!=objList.end(); ++it)
	{
		if(*it == o)
		{
			objList.erase(it);
			dynamicsWorld->removeRigidBody(o->getBody());
			return true;
		}
	}
	return false;

}

int playedSound = 0;

bool Simulator::stepSimulation (const Ogre::Real elapsedTime, Mix_Music* music,
								int maxSubSteps, 
								const Ogre::Real fixedTimestep
								)
{
	Mix_Chunk* chunk;
	dynamicsWorld->stepSimulation(elapsedTime, maxSubSteps, fixedTimestep);
	// dynamicsWorld->stepSimulation(1 / 60.f, 10);
	// std::cout << objList.size() << std::endl;
	// Ogre::Vector3 ball;
	// for (std::deque<GameObject*>::iterator it = objList.begin(); it!=objList.end(); ++it)
	// {
	// 	GameObject* obj = *it;
	// 	btRigidBody* body = obj->getBody();
	// 	if (body && body->getMotionState()){
	// 		btTransform trans;
	// 		body->getMotionState()->getWorldTransform(trans);

	// 		void *nodePointer = body->getUserPointer();
	// 		if (nodePointer) {
	// 			btQuaternion orientation = trans.getRotation();
	// 			Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(nodePointer);
	// 			sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
	// 			if(obj->name == "ball" || obj->name == "ball1"){
	// 				ball = sceneNode->getPosition();
	// 			}
	// 			// std::cout << "elapsedTime == " << elapsedTime <<": sphere x: " << trans.getOrigin().getX();
 //    //     std::cout << "  sphere y: " << trans.getOrigin().getY();
 //    //     std::cout << "  sphere z: " << trans.getOrigin().getZ() << std::endl;
	// 			sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
	// 			// sceneNode->rotate (Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));

	// 		}
	// 	}

	// }
	// playedSound--;

	// if((Ogre::Math::Abs(ball.x) >= 240 || Ogre::Math::Abs(ball.y) >= 240 || Ogre::Math::Abs(ball.z) >= 240)){
	// 	if(playedSound <= 0)
	// 	{
	// 	    chunk = Mix_LoadWAV("Soccer_Ball_Bounce_On_Pavement.wav");
	// 	    playedSound = 30;
	// 	    Mix_PlayChannel( 0, chunk, 0 );

	// 	}
	// 	else
	// 		playedSound = 20;

	// }
	// else{
	// 	chunk = NULL;
	// }



	// if(!scored)
	// {
	// 	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	//     for (int i=0;i<numManifolds;i++)
	//     {
	//         btPersistentManifold* contactManifold =  dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
	//         const btCollisionObject* obA = static_cast<const btCollisionObject*>(contactManifold->getBody0());
	//         const btCollisionObject* obB = static_cast<const btCollisionObject*>(contactManifold->getBody1());

	//         void *nodePointerA = obA->getUserPointer();
	//         void *nodePointerB = obB->getUserPointer();
	// 			if (nodePointerA) {
	// 				Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(nodePointerA);
	// 				std::cout << "A NAME IS : " << sceneNode->getName() << std::endl;
	// 				//return true;
	// 			}
	// 			if (nodePointerB) {
	// 				Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(nodePointerA);
	// 				if(sceneNode)
	// 					std::cout << "B NAME IS : " << sceneNode->getName() << std::endl;
	// 				//return true;
	// 			}
	//     }
	// }
    return false;
}

btDiscreteDynamicsWorld* Simulator::getDynamicsWorld()
{

	return dynamicsWorld;
}


void Simulator::destroyNode(Ogre::SceneNode* node)
{
	if(!node) return;

	// Destroy all the attached objects
	Ogre::SceneNode::ObjectIterator itObject = node->getAttachedObjectIterator();

	while ( itObject.hasMoreElements() )
	  node->getCreator()->destroyMovableObject(itObject.getNext());

	// Recurse to child SceneNodes
	Ogre::SceneNode::ChildNodeIterator itChild = node->getChildIterator();

	while ( itChild.hasMoreElements() )
	{
	  Ogre::SceneNode* pChildNode = static_cast<Ogre::SceneNode*>(itChild.getNext());
	  destroyNode( pChildNode );
	}
}

void Simulator::reload()
{
	// Ball* newBall;
	// for (std::deque<GameObject*>::iterator it = objList.begin(); it!=objList.end(); ++it)
	// {
	// 	GameObject* obj = *it;
	// 	if(obj->name == "ball")
	// 	{
	// 		Simulator* sim = obj->simulator;
	// 		Ogre::SceneManager* mgr = obj->sceneMgr;
	// 		Ogre::SceneNode* node = obj->rootNode;
	// 		destroyNode(node);
	// 		node->removeAndDestroyAllChildren();
	// 		node->getCreator()->destroySceneNode(node);
	// 		delete obj;
	// 		Ogre::SceneNode* newNode;
	// 		newBall = new Ball("ball", mgr, sim, newNode, 90., Ogre::Vector3(0,-240,210));
 //    		newBall->create();
 //    		break;
 //    	}
	// }
}