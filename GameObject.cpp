#include "GameObject.h"

GameObject::GameObject(Ogre::String n,
	Ogre::SceneManager* mgr,
	Ogre::SceneNode* node,
	btScalar m) : 
	name(n), sceneMgr(mgr), rootNode(node), mass(m)
{
	
}

GameObject::~GameObject()
{
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
	Ogre::SceneNode* node,
	btScalar m,
	Ogre::Vector3 pos) :
	GameObject(n,mgr,node,m),
	position(pos)
{
    inMotion = false;
	inertia = btVector3(0,0,0);
    health = 100;
}

Player::~Player()
{
}

void Player::create(Ogre::Degree p, Ogre::Degree r, Ogre::Degree y)
{
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
}

bool Player::move(int dir, Ogre::Vector3 p)
{
    if(canMove())
    {
        direction = dir;
        endPos = p;
        inMotion = true;
        return true;
    }
    else
    {
        return false;
    }
}


bool Player::simulate(const Ogre::Real elapsedTime)
{
    if(inMotion)
    {
        Ogre::Vector3 nowPos = rootNode->getPosition();
        if(direction == 0)
        {
            rootNode->setPosition(Ogre::Vector3(nowPos.x, nowPos.y, nowPos.z - moveSpeed() * elapsedTime));
            if(rootNode->getPosition().z < endPos.z)
            {
                playerX -= 1;
                inMotion = false;
                return true;
            }
        }
        else if(direction == 1)
        {
            rootNode->setPosition(Ogre::Vector3(nowPos.x + moveSpeed() * elapsedTime, nowPos.y, nowPos.z));
            if(rootNode->getPosition().x > endPos.x)
            {
                playerY += 1;
                inMotion = false;
                return true;
            }
        }
        else if(direction == 2)
        {
            rootNode->setPosition(Ogre::Vector3(nowPos.x, nowPos.y, nowPos.z + moveSpeed() * elapsedTime));
            if(rootNode->getPosition().z > endPos.z)
            {
                playerX += 1;
                inMotion = false;
                return true;
            }
        }
        else if(direction == 3)
        {
            rootNode->setPosition(Ogre::Vector3(nowPos.x - moveSpeed() * elapsedTime, nowPos.y, nowPos.z));
            if(rootNode->getPosition().x < endPos.x)
            {
                playerY -= 1;
                inMotion = false;
                return true;
            }
        }
    }
    return false;
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

void Player::changeMaterial(std::string s)
{
    Ogre::Entity* mEntity = static_cast<Ogre::Entity*>(rootNode->getAttachedObject(0));
    mEntity->setMaterialName(s);
}

Wall::Wall(Ogre::String n,
    Ogre::SceneManager* mgr,
    Ogre::SceneNode* node,
    btScalar m, double x, double y, Ogre::Vector3 norm, int dist):
    GameObject(n,mgr,node,m),
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
    Ogre::SceneNode* node,
    btScalar m,
    Ogre::Vector3 pos) :
    GameObject(n,mgr,node,m),
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
// void Simulator::destroyNode(Ogre::SceneNode* node)
// {
// 	if(!node) return;

// 	// Destroy all the attached objects
// 	Ogre::SceneNode::ObjectIterator itObject = node->getAttachedObjectIterator();

// 	while ( itObject.hasMoreElements() )
// 	  node->getCreator()->destroyMovableObject(itObject.getNext());

// 	// Recurse to child SceneNodes
// 	Ogre::SceneNode::ChildNodeIterator itChild = node->getChildIterator();

// 	while ( itChild.hasMoreElements() )
// 	{
// 	  Ogre::SceneNode* pChildNode = static_cast<Ogre::SceneNode*>(itChild.getNext());
// 	  destroyNode( pChildNode );
// 	}
// }

// void Simulator::reload()
// {
// 	Ball* newBall;
// 	for (std::deque<GameObject*>::iterator it = objList.begin(); it!=objList.end(); ++it)
// 	{
// 		GameObject* obj = *it;
// 		if(obj->name == "ball")
// 		{
// 			Simulator* sim = obj->simulator;
// 			Ogre::SceneManager* mgr = obj->sceneMgr;
// 			Ogre::SceneNode* node = obj->rootNode;
// 			destroyNode(node);
// 			node->removeAndDestroyAllChildren();
// 			node->getCreator()->destroySceneNode(node);
// 			delete obj;
// 			Ogre::SceneNode* newNode;
// 			newBall = new Ball("ball", mgr, sim, newNode, 90., Ogre::Vector3(0,-240,210));
//     		newBall->create();
//     		break;
//     	}
// 	}
// }