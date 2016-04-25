#include "GameObject.h"
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


GameObject::GameObject(Ogre::String n,
	Ogre::SceneManager* mgr,
	Ogre::SceneNode* node,
	btScalar m) : 
	name(n), sceneMgr(mgr), rootNode(node), mass(m)
{
	
}

GameObject::~GameObject()
{

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
    key = false;
    burn = 0;
    oxygen = 10;
    poison = false;
    level =0;
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
    rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode("playerNode", newPos);
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
    return (!inMotion && isAlive());
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

void Player::gotKey()
{
    key = true;
}

bool Player::hasKey()
{
    return key;
}
void Player::updateStatus()
{
    Ogre::Entity* mEntity = static_cast<Ogre::Entity*>(rootNode->getAttachedObject(0));
    if(!isAlive())
    {
        // std::string newMaterial = "Tile/Rakan";
        //  mEntity->setMaterialName(newMaterial);
    }
    else if(poison && burn >0)
    {
         std::string newMaterial = "Cube/PBurn" + patch::to_string(burn);
         mEntity->setMaterialName(newMaterial);
         damageTaken(burnDamage()+poisonDamage());
    }
    else if(poison && oxygen<10)
    {
        std::string newMaterial = "Cube/PBubble" + patch::to_string(oxygen);
         mEntity->setMaterialName(newMaterial);
         damageTaken(poisonDamage());
    }
    else if(burn > 0)
    {
         std::string newMaterial = "Cube/Burn" + patch::to_string(burn);
         mEntity->setMaterialName(newMaterial);
         damageTaken(burnDamage());
    }
    else if (poison)
    {
        mEntity->setMaterialName("Cube/Poison");
        damageTaken(poisonDamage());
    }
    else if(oxygen < 10 && oxygen >= 1)
    {
         std::string newMaterial = "Cube/Bubble" + patch::to_string(oxygen);
         mEntity->setMaterialName(newMaterial);
    }
    else
                mEntity->setMaterialName("Cube/Blend");
     burn -= 1;
}

void Player::removeBurn()
{
    burn = 0;
}

void Player::damageTaken(double damage)
{
    health -= damage;
    if(health <= 0)
    {
        kill();
    }
}

void Player::oxygenLost(int amount)
{
    oxygen -= amount;
    if(oxygen <= 0)
    {
        kill();
    }
}

void Player::breath()
{
    if(isAlive())
        oxygen = 10;
}

void Player::kill()
{
    std::cout << "player killed" << std::endl;
    health = 0;
    Ogre::Entity* mEntity = static_cast<Ogre::Entity*>(rootNode->getAttachedObject(0));
    if(poison)   
    {       
        mEntity->setMaterialName("Cube/DeathPoison");       
    }       
    else if(burn>0)     
    {       
         mEntity->setMaterialName("Cube/DeathFire");        
    }       
    else        
    {       
        mEntity->setMaterialName("Cube/DeathDrown");        
    }
}

bool Player::isAlive()
{
    return (health > 0 && oxygen > 0);
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
	Ogre::Entity* entity = sceneMgr->createEntity(name); 
    sceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entity); 
    entity->setMaterialName("Examples/Rocky"); 
    entity->setCastShadows(false);
}