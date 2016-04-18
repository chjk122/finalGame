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
	Ball* ball,
	Ogre::Vector3 pos,
	Ogre::Real score) :
	GameObject(n,mgr,sim,node,m),
	playerBall(ball),
	position(pos),
	points(score)
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

void Player::scored()
{
	points+=1;
}


Ball::Ball(Ogre::String n,
	Ogre::SceneManager* mgr,
	Simulator* sim,
	Ogre::SceneNode* node,
	btScalar m, Ogre::Vector3 pos) :
	GameObject(n,mgr,sim,node,m),
	position(pos)
{
	inertia = btVector3(0,0,0);
}

Ball::~Ball()
{
}

void Ball::create()
{
	Ogre::MeshManager::getSingleton().create("Soccer_ball.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		Ogre::Entity* entity = sceneMgr->createEntity(Ogre::MeshManager::getSingleton().getByName("Soccer_ball.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));


    entity->setCastShadows(true);
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name, position);
    rootNode->attachObject(entity);
    // rootNode->setScale(0.10, 0.10, 0.10);
    rootNode->setScale(1.8, 1.8, 1.8);


    shape = new btSphereShape(10);
    motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position.x, position.y, position.z)));
    shape->calculateLocalInertia(mass, inertia);

    btRigidBody::btRigidBodyConstructionInfo shapeRBInfo(mass, motionState, shape, inertia);
    body = new btRigidBody(shapeRBInfo);
    body->setRestitution(1); //bouncing
    // body->setFriction(50.0);
    // body->setRollingFriction(20.3f);
    body->setDamping(0.02f, 0.8f);
	body->setUserPointer(rootNode);


    simulator->addObject(this);

    // for (int i = 0; i < 1000; i++) {
    //     simulator->getDynamicsWorld()->stepSimulation(1 / 60.f, 10);

    //     btTransform trans;
    //     body->getMotionState()->getWorldTransform(trans);

    //     std::cout << "i == " << i <<": sphere x: " << trans.getOrigin().getX();
    //     std::cout << "  sphere y: " << trans.getOrigin().getY();
    //     std::cout << "  sphere z: " << trans.getOrigin().getZ() << std::endl;
    // }
}
void Ball::kickBall(btScalar power, btScalar angle, btScalar height)
{
	power = power * 2.5;
	body->activate();
	body->applyCentralImpulse(btVector3(-angle * power, -(height+.1)*power, power));
}

void Ball::setGhostBallPos(float x, float y, float z){

	rootNode->setPosition(x,y,z);

}


GhostBall::GhostBall(Ogre::String n,
	Ogre::SceneManager* mgr,
	Simulator* sim,
	Ogre::SceneNode* node,
	btScalar m, Ogre::Vector3 pos) :
	Ball(n,mgr,sim,node,m,pos)
{
}

GhostBall::~GhostBall()
{
}

void GhostBall::create()
{
	Ogre::MeshManager::getSingleton().create("Soccer_ball.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		Ogre::Entity* entity = sceneMgr->createEntity(Ogre::MeshManager::getSingleton().getByName("Soccer_ball.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));

    entity->setCastShadows(true);
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name, position);
    rootNode->attachObject(entity);
    rootNode->setScale(1.8, 1.8, 1.8);
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

Goal::Goal(Ogre::String n,
    Ogre::SceneManager* mgr,
    Simulator* sim,
    Ogre::SceneNode* node,
    btScalar m, double x, double y, Ogre::Vector3 norm, int dist):
    Wall(n,mgr,sim,node,m, x, y, norm, dist)
{

}
Goal::~Goal()
{

}

void Goal::create()
{
    Ogre::Plane plane(normal, +10);

    Ogre::Vector3 up = Ogre::Vector3::UNIT_Y;
    Ogre::MeshManager::getSingleton().createPlane(name, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
        xLength,yLength,20,20,true,1,5,5,up);

    btTransform goal;
    goal.setIdentity();
    // if(norm.x < 0 || norm.y < 0 || norm.z < 0)  //roof, posZ, posX
    //     goal.setOrigin(btVector3((distFromCenter*norm.x)+(5*norm.x), (distFromCenter*norm.y) - (5*norm.y) + 5, (distFromCenter*norm.z) - (norm.z *5)));
    // else
    // double xTrans;
    // double yTrans;
    srand(static_cast<unsigned int>(time(0)));
    int value = 22; 
    while(value == 22)
    {
    	value =(int)(rand()%25);
    }
    this->xTrans = -200 + (value%5)*100;
    this->yTrans = 200 - (value/5)*100;
        goal.setOrigin(btVector3(this->xTrans, this->yTrans, distFromCenter -10 +1.6));



    inertia = btVector3(0,0,0);

    // btScalar x1(xLength/(2.));
    // btScalar y1(yLength/(2.));
    // btScalar z1(10.);
    btScalar x1(xLength/2.);
    btScalar y1(yLength/2.);
    btScalar z1(10.);

    shape = new btBoxShape(btVector3(x1, y1, z1));
    motionState = new btDefaultMotionState(goal);
    shape->calculateLocalInertia(mass, inertia);

    btRigidBody::btRigidBodyConstructionInfo groundRBInfo(mass, motionState, shape, inertia);
    body = new btRigidBody(groundRBInfo);
    body->setRestitution(.5);
    // body->setUserPointer(rootNode);


	Ogre::Entity* entity = sceneMgr->createEntity(name); 
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
    rootNode->attachObject(entity);
    rootNode->translate(Ogre::Vector3(xTrans,yTrans,0));
    entity->setMaterialName("Examples/GrassFloor"); 
    entity->setCastShadows(false);

    body->setUserPointer(rootNode);
    simulator->addObject(this);
}

bool Goal::ballScored(Ogre::Vector3 pos)
{
	//neg Z wall (player 1's goal is)
	if(this->normal == Ogre::Vector3::UNIT_Z)
	{
		if((pos.x >= xTrans - 50) && (pos.x <= xTrans + 50) && (pos.y >= yTrans - 50) && (pos.y <= yTrans + 50) && (pos.z <= -240))
		{
			return true;
		}
		return false;
	}
	if(this->normal == Ogre::Vector3::NEGATIVE_UNIT_Z)
	{
		if((pos.x >= xTrans - 50 && pos.x <= xTrans + 50) && (pos.y >= yTrans - 50 && pos.y <= yTrans + 50) && pos.z <= +240)
		{
			return true;
		}
		return false;
	}
}

/*--------------------------------------Tile ------------------------------------------*/
Tile::Tile(Ogre::String n,
    Ogre::SceneManager* mgr,
    Simulator* sim,
    Ogre::SceneNode* node,
    btScalar m, double x, double z, Ogre::Vector3 pos, Ogre::Vector3 norm, int dist):
    GameObject(n,mgr,sim,node,m),
    xLength(x), zLength(z), position(pos), normal(norm), distFromCenter(dist)
{

}
Tile::~Tile()
{

}

void Tile::create()
{
	Ogre::Plane plane(normal, +10);

    Ogre::Vector3 up = Ogre::Vector3::UNIT_Z;
    Ogre::MeshManager::getSingleton().createPlane(name, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
        xLength,zLength,20,20,true,1,5,5,up);

    btTransform tile;
    tile.setIdentity();
    // if(norm.x < 0 || norm.y < 0 || norm.z < 0)  //roof, posZ, posX
    //     goal.setOrigin(btVector3((distFromCenter*norm.x)+(5*norm.x), (distFromCenter*norm.y) - (5*norm.y) + 5, (distFromCenter*norm.z) - (norm.z *5)));
    // else
    // double xTrans;
    // double yTrans;
    // srand(static_cast<unsigned int>(time(0)));
    // int value = 22; 
    // while(value == 22)
    // {
    // 	value =(int)(rand()%25);
    // }
    // this->xTrans = -200 + (value%5)*100;
    // this->yTrans = 200 - (value/5)*100;
    tile.setOrigin(btVector3(position.x, position.y, position.z));
    inertia = btVector3(0,0,0);

    // btScalar x1(xLength/(2.));
    // btScalar y1(yLength/(2.));
    // btScalar z1(10.);
    btScalar x1(xLength/2.);
    btScalar y1(10.);
    btScalar z1(zLength/2.);

    shape = new btBoxShape(btVector3(x1, y1, z1));
    motionState = new btDefaultMotionState(tile);
    shape->calculateLocalInertia(mass, inertia);

    btRigidBody::btRigidBodyConstructionInfo groundRBInfo(mass, motionState, shape, inertia);
    body = new btRigidBody(groundRBInfo);
    body->setRestitution(.5);
    // body->setUserPointer(rootNode);


	Ogre::Entity* entity = sceneMgr->createEntity(name); 
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
    rootNode->attachObject(entity);
    //rootNode->translate(Ogre::Vector3(xTrans,yTrans,0));
    entity->setMaterialName("Examples/GrassFloor"); 
    entity->setCastShadows(false);

    body->setUserPointer(rootNode);
    simulator->addObject(this);
}
/*------------------------------------PathTile ------------------------------------------*/
PathTile::PathTile(Ogre::String n,
    Ogre::SceneManager* mgr,
    Simulator* sim,
    Ogre::SceneNode* node,
    btScalar m, double x, double z, Ogre::Vector3 pos, Ogre::Vector3 norm, int dist):
    Tile(n,mgr,sim,node,m, x, z, pos, norm,  dist)
{

}
PathTile::~PathTile()
{

}

void PathTile::create()
{
	Ogre::Plane plane(normal, +10);

    Ogre::Vector3 up = Ogre::Vector3::UNIT_Z;
    Ogre::MeshManager::getSingleton().createPlane(name, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
        xLength,zLength,20,20,true,1,5,5,up);

    btTransform tile;
    tile.setIdentity();
    // if(norm.x < 0 || norm.y < 0 || norm.z < 0)  //roof, posZ, posX
    //     goal.setOrigin(btVector3((distFromCenter*norm.x)+(5*norm.x), (distFromCenter*norm.y) - (5*norm.y) + 5, (distFromCenter*norm.z) - (norm.z *5)));
    // else
    // double xTrans;
    // double yTrans;
    // srand(static_cast<unsigned int>(time(0)));
    // int value = 22; 
    // while(value == 22)
    // {
    // 	value =(int)(rand()%25);
    // }
    // this->xTrans = -200 + (value%5)*100;
    // this->yTrans = 200 - (value/5)*100;
    tile.setOrigin(btVector3(position.x, position.y, position.z));
    inertia = btVector3(0,0,0);

    // btScalar x1(xLength/(2.));
    // btScalar y1(yLength/(2.));
    // btScalar z1(10.);
    btScalar x1(xLength/2.);
    btScalar y1(10.);
    btScalar z1(zLength/2.);

    shape = new btBoxShape(btVector3(x1, y1, z1));
    motionState = new btDefaultMotionState(tile);
    shape->calculateLocalInertia(mass, inertia);

    btRigidBody::btRigidBodyConstructionInfo groundRBInfo(mass, motionState, shape, inertia);
    body = new btRigidBody(groundRBInfo);
    body->setRestitution(.5);
    // body->setUserPointer(rootNode);


	Ogre::Entity* entity = sceneMgr->createEntity(name); 
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
    rootNode->attachObject(entity);
    //rootNode->translate(Ogre::Vector3(xTrans,yTrans,0));
    entity->setMaterialName("Examples/GrassFloor"); 
    entity->setCastShadows(false);

    body->setUserPointer(rootNode);
    simulator->addObject(this);
}
/*-----------------------------OutterTile----------------------------------*/
OutterTile::OutterTile(Ogre::String n,
    Ogre::SceneManager* mgr,
    Simulator* sim,
    Ogre::SceneNode* node,
    btScalar m, double x, double z, Ogre::Vector3 pos, Ogre::Vector3 norm, int dist):
    Tile(n,mgr,sim,node,m, x, z, pos, norm,  dist)
{

}
OutterTile::~OutterTile()
{

}

void OutterTile::create()
{
	Ogre::Plane plane(normal, +10);

    Ogre::Vector3 up = Ogre::Vector3::UNIT_Z;
    Ogre::MeshManager::getSingleton().createPlane(name, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
        xLength,zLength,20,20,true,1,5,5,up);

    btTransform tile;
    tile.setIdentity();
    // if(norm.x < 0 || norm.y < 0 || norm.z < 0)  //roof, posZ, posX
    //     goal.setOrigin(btVector3((distFromCenter*norm.x)+(5*norm.x), (distFromCenter*norm.y) - (5*norm.y) + 5, (distFromCenter*norm.z) - (norm.z *5)));
    // else
    // double xTrans;
    // double yTrans;
    // srand(static_cast<unsigned int>(time(0)));
    // int value = 22; 
    // while(value == 22)
    // {
    // 	value =(int)(rand()%25);
    // }
    // this->xTrans = -200 + (value%5)*100;
    // this->yTrans = 200 - (value/5)*100;
    tile.setOrigin(btVector3(position.x, position.y, position.z));
    inertia = btVector3(0,0,0);

    // btScalar x1(xLength/(2.));
    // btScalar y1(yLength/(2.));
    // btScalar z1(10.);
    btScalar x1(xLength/2.);
    btScalar y1(10.);
    btScalar z1(zLength/2.);

    shape = new btBoxShape(btVector3(x1, y1, z1));
    motionState = new btDefaultMotionState(tile);
    shape->calculateLocalInertia(mass, inertia);

    btRigidBody::btRigidBodyConstructionInfo groundRBInfo(mass, motionState, shape, inertia);
    body = new btRigidBody(groundRBInfo);
    body->setRestitution(.5);
    // body->setUserPointer(rootNode);


	Ogre::Entity* entity = sceneMgr->createEntity(name); 
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
    rootNode->attachObject(entity);
    //rootNode->translate(Ogre::Vector3(xTrans,yTrans,0));
    entity->setMaterialName("Examples/GrassFloor"); 
    entity->setCastShadows(false);

    body->setUserPointer(rootNode);
    simulator->addObject(this);
}

bool OutterTile::healthDamage(Ogre::Vector3 pos)
{
	if((pos.x >= position.x - distFromCenter) && (pos.x <= position.x + distFromCenter) && (pos.z >= position.z - distFromCenter) && (pos.z <= position.z + distFromCenter))
		{
			return true;
		}
		return false;
}


/*--------------------------------end of tile--------------------------------*/
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
	dynamicsWorld->setGravity(btVector3(0.0, -98., 0.0));
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
	Ogre::Vector3 ball;
	for (std::deque<GameObject*>::iterator it = objList.begin(); it!=objList.end(); ++it)
	{
		GameObject* obj = *it;
		btRigidBody* body = obj->getBody();
		if (body && body->getMotionState()){
			btTransform trans;
			body->getMotionState()->getWorldTransform(trans);

			void *nodePointer = body->getUserPointer();
			if (nodePointer) {
				btQuaternion orientation = trans.getRotation();
				Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(nodePointer);
				sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
				if(obj->name == "ball" || obj->name == "ball1"){
					ball = sceneNode->getPosition();
				}
				// std::cout << "elapsedTime == " << elapsedTime <<": sphere x: " << trans.getOrigin().getX();
    //     std::cout << "  sphere y: " << trans.getOrigin().getY();
    //     std::cout << "  sphere z: " << trans.getOrigin().getZ() << std::endl;
				sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
				// sceneNode->rotate (Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));

			}
		}

	}
	playedSound--;

	if((Ogre::Math::Abs(ball.x) >= 240 || Ogre::Math::Abs(ball.y) >= 240 || Ogre::Math::Abs(ball.z) >= 240)){
		if(playedSound <= 0)
		{
		    chunk = Mix_LoadWAV("Soccer_Ball_Bounce_On_Pavement.wav");
		    playedSound = 30;
		    Mix_PlayChannel( 0, chunk, 0 );

		}
		else
			playedSound = 20;

	}
	else{
		chunk = NULL;
	}



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

	Ball *ball1 = 0;
	Ball *ball2 = 0;
	Goal *goal1 = 0;
	Goal *goal2 = 0;
	for (std::deque<GameObject*>::iterator it = objList.begin(); it!=objList.end(); ++it)
	{
		GameObject* obj = *it;
		btRigidBody* body = obj->getBody();
		if (body && body->getMotionState()){
			btTransform trans;
			body->getMotionState()->getWorldTransform(trans);

			void *nodePointer = body->getUserPointer();
			if (nodePointer) {
				Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(nodePointer);
				if(obj->name == "ball" || obj->name == "ball1"){
					ball1 = dynamic_cast<Ball *>(obj);
				}
				else if(obj->name == "ball2"){
					ball2 = dynamic_cast<Ball *>(obj);
				}
				else if(obj->name == "goal" || obj->name == "goal1"){
					goal1 = dynamic_cast<Goal *>(obj);
				}
				else if(obj->name == "goal2"){
					goal2 = dynamic_cast<Goal *>(obj);
				}				

			}
		}

	}
	bool ball1scored = 0;
	bool ball2scored = 0;
	if(goal1 && ball1)
		ball1scored = goal1->ballScored(ball1->rootNode->getPosition());
	if(goal2 && ball2)
		ball2scored = goal2->ballScored(ball2->rootNode->getPosition());

	if(ball1scored)
	{
		return true;
	}


    return false;
	//physics will work but collision wont say when it happens
}

btDiscreteDynamicsWorld* Simulator::getDynamicsWorld()
{

	return dynamicsWorld;
}


void Simulator::kickBall(btScalar power, btScalar angle, btScalar height){

	for (std::deque<GameObject*>::iterator it = objList.begin(); it!=objList.end(); ++it)
	{
		GameObject* obj = *it;
		if(obj->name == "ball"){
			dynamic_cast<Ball *>(obj)->kickBall(power, angle, height);
			return;
		}
	}
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

Ball* Simulator::reload()
{
	Ball* newBall;
	for (std::deque<GameObject*>::iterator it = objList.begin(); it!=objList.end(); ++it)
	{
		GameObject* obj = *it;
		if(obj->name == "ball")
		{
			Simulator* sim = obj->simulator;
			Ogre::SceneManager* mgr = obj->sceneMgr;
			Ogre::SceneNode* node = obj->rootNode;
			destroyNode(node);
			node->removeAndDestroyAllChildren();
			node->getCreator()->destroySceneNode(node);
			delete obj;
			Ogre::SceneNode* newNode;
			newBall = new Ball("ball", mgr, sim, newNode, 90., Ogre::Vector3(0,-240,210));
    		newBall->create();
    		break;
    	}
	}
	for (std::deque<GameObject*>::iterator it = objList.begin(); it!=objList.end(); ++it)
	{
		GameObject* obj = *it;
		if(obj->name == "goal")
		{
			Simulator* sim = obj->simulator;
			Ogre::SceneManager* mgr = obj->sceneMgr;
			Ogre::SceneNode* node = obj->rootNode;
			destroyNode(node);
			node->removeAndDestroyAllChildren();
			node->getCreator()->destroySceneNode(node);
			delete obj;
			Ogre::SceneNode* newNode;
			Goal* goal = new Goal("goal", mgr, sim, newNode, 0.,100, 100, Ogre::Vector3::UNIT_Z, -249.6);
		 	goal->create();
		 	break;
		}
	}

	return newBall;
}