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
    inMotion = false;
	inertia = btVector3(0,0,0);
}

Player::~Player()
{
}

void Player::create(Ogre::Degree p, Ogre::Degree r, Ogre::Degree y)
{
	// Ogre::MeshManager::getSingleton().create("outfit_soccer_player_shirt1.001.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	// Ogre::Entity* entity = sceneMgr->createEntity(Ogre::MeshManager::getSingleton().getByName(
	// 	"outfit_soccer_player_shirt1.001.mesh", 
	// 	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));

    Ogre::MeshManager::getSingleton().create("cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::Entity* entity = sceneMgr->createEntity(Ogre::MeshManager::getSingleton().getByName(
     "cube.mesh", 
     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));
    Ogre::Vector3 newPos(position.x, position.y, position.z);
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name, newPos);
    rootNode->setScale(length()/100.0, length()/100.0, length()/100.0);
    rootNode->attachObject(entity);
    // rootNode->setScale(.6, .6, .6);
    entity->setMaterialName("Cube/Blend"); 
    rootNode->pitch(Ogre::Degree(p));
    rootNode->roll(Ogre::Degree(r));

    shape = new btBoxShape(btVector3(Player::length(),Player::length(),Player::length()));
    motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position.x, position.y, position.z)));
    shape->calculateLocalInertia(mass, inertia);

    btRigidBody::btRigidBodyConstructionInfo shapeRBInfo(mass, motionState, shape, inertia);
    body = new btRigidBody(shapeRBInfo);
    body->setRestitution(1); //bouncing
    // body->setFriction(50.0);
    // body->setRollingFriction(20.3f);
    body->setDamping(0.02f, 0.8f);
    body->setLinearFactor(btVector3(1,0,1)); // unable to move in the Y
    body->setUserPointer(rootNode);


    simulator->addObject(this);
}

bool Player::move(int dir, Ogre::Vector3 p)
{
    if(canMove())
    {
        // p.y = p.y + (length()/2);
        direction = dir;
        endPos = p;
        double xDir = 0.0;
        double zDir = 0.0;
        if(dir == 0)
        {
            zDir = -1.0;
            xDir = 0.0;
        }
        else if(dir == 1)
        {
            xDir = 1.0;
            zDir = 0.0;
        }
        else if(dir == 2)
        {
            zDir = 1.0;
            xDir = 0.0;
        }
        else if(dir == 3)
        {
            xDir = -1.0;
            zDir = 0.0;
        }
        btVector3 linDirection(xDir * moveSpeed(), 0.0, zDir * moveSpeed());
        body->setLinearVelocity(linDirection);
        std::cout << "moving in x " << xDir << "moving in z " << zDir << std::endl;
        inMotion = true;
        return true;
    }
    else
    {
        return false;
    }
}


void Player::simulate(const Ogre::Real elapsedTime)
{
    if(inMotion)
    {
        // btTransform trans;
        // body->getMotionState()->getWorldTransform(trans);
        // std::cout << trans.getOrigin().getX() << ", " << trans.getOrigin().getY() << ", " << trans.getOrigin().getZ() << std::endl;
        // rootNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
        Ogre::Vector3 nowPos = rootNode->getPosition();
        if(direction == 0)
        {
            rootNode->setPosition(Ogre::Vector3(nowPos.x, nowPos.y, nowPos.z - moveSpeed() * elapsedTime));
            if(rootNode->getPosition().z < endPos.z)
            {
                body->setLinearVelocity(btVector3(0.0,0.0,0.0));
                // rootNode->setPosition(endPos);
                playerX -= 1;
                inMotion = false;
            }
        }
        else if(direction == 1)
        {
            rootNode->setPosition(Ogre::Vector3(nowPos.x + moveSpeed() * elapsedTime, nowPos.y, nowPos.z));
            if(rootNode->getPosition().x > endPos.x)
            {
                std::cout << "stopped in 1" << std::endl;
                body->setLinearVelocity(btVector3(0.0,0.0,0.0));
                // rootNode->setPosition(endPos);
                playerY += 1;
                inMotion = false;
            }
        }
        else if(direction == 2)
        {
            rootNode->setPosition(Ogre::Vector3(nowPos.x, nowPos.y, nowPos.z + moveSpeed() * elapsedTime));
            if(rootNode->getPosition().z > endPos.z)
            {
                std::cout << "stopped in 2" << std::endl;
                body->setLinearVelocity(btVector3(0.0,0.0,0.0));
                // rootNode->setPosition(endPos);
                playerX += 1;
                inMotion = false;
            }
        }
        else if(direction == 3)
        {
            rootNode->setPosition(Ogre::Vector3(nowPos.x - moveSpeed() * elapsedTime, nowPos.y, nowPos.z));
            if(rootNode->getPosition().x < endPos.x)
            {
                std::cout << "stopped in 3" << std::endl;
                body->setLinearVelocity(btVector3(0.0,0.0,0.0));
                // rootNode->setPosition(endPos);
                playerY -= 1;
                inMotion = false;
            }
        }
    }
}

bool Player::canMove()
{
    return (!inMotion);
}

int Player::getPlayerX()
{
    return playerX;
}
int Player::getPlayerY()
{
    return playerY;
}   

void Player::setPlayerCord(int xI, int yI, int lengthTile, double xCord, double zCord)
{
    playerX = xI;
    playerY = yI;
    Ogre::Vector3 newPos(xCord + (yI * lengthTile), position.y + (length()/2), zCord+ (xI * lengthTile));
    position = newPos;
    this->create();
    rootNode->setPosition(newPos);
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

    // btTransform groundTransform;
    // groundTransform.setIdentity();
    // groundTransform.setOrigin(btVector3((distFromCenter*normal.x)-(10*normal.x), (distFromCenter*normal.y) - (10*normal.y), (distFromCenter*normal.z) - (normal.z *10)));
    // inertia = btVector3(0,0,0);

    // btScalar x1(250.);
    // btScalar y1(250.);
    // btScalar z1(250.);

    // if(normal.x != 0){
    //     x1 = 10.;
    // }
    // else if(normal.y != 0){
    //     y1 = 10.;
    // }
    // else if(normal.z != 0) {
    //     z1 = 10.;
    // }

    // shape = new btBoxShape(btVector3(x1, y1, z1));
    // motionState = new btDefaultMotionState(groundTransform);
    // shape->calculateLocalInertia(mass, inertia);

    // btRigidBody::btRigidBodyConstructionInfo groundRBInfo(mass, motionState, shape, inertia);
    // body = new btRigidBody(groundRBInfo);
    // body->setRestitution(.5);
    // body->setFriction(50.0);
    // body->setRollingFriction(20.3f);


    // simulator->addObject(this);
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
	Ogre::Vector3 playePos;
	for (std::deque<GameObject*>::iterator it = objList.begin(); it!=objList.end(); ++it)
	{
		GameObject* obj = *it;
		btRigidBody* body = obj->getBody();
		if (body && body->getMotionState()){
			btTransform trans;
			body->getMotionState()->getWorldTransform(trans);

			void *nodePointer = body->getUserPointer();
            // body->setLinearVelocity( Ogre::Vector3::NEGATIVE_UNIT_Z * 5.f);
			if (nodePointer) {
				btQuaternion orientation = trans.getRotation();
				Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(nodePointer);
				// sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
				if(obj->name == "player"){
                    Player *playerObj = dynamic_cast<Player *>(obj);
                    playerObj->simulate(elapsedTime);
					// playePos = sceneNode->getPosition();
     //                btVector3 direction(0.0, 0.0, -5.0);
     //                body->setLinearVelocity( direction);
                    //body->setLinearVelocity( direction * 30.f);
                    // std::cout << body->getLinearVelocity() << std::endl;
                    // sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
				}
				// std::cout << "elapsedTime == " << elapsedTime <<": sphere x: " << trans.getOrigin().getX();
    //     std::cout << "  sphere y: " << trans.getOrigin().getY();
    //     std::cout << "  sphere z: " << trans.getOrigin().getZ() << std::endl;
				// sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
				// sceneNode->rotate (Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));

			}
		}

	}
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