#include "Cubester.h"

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

Ogre::Vector3 AbstractCubester::getPosition()
{
    return position;
}
void AbstractCubester::create(std::string material)
{
    Ogre::MeshManager::getSingleton().create("cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    ent = mgr->createEntity(Ogre::MeshManager::getSingleton().getByName(
        "cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));
    name = patch::to_string(getX()) + "enemy" + patch::to_string(getY());
    Ogre::Vector3 newPos(position.x, position.y + length()/2, position.z);
    position = newPos;
    rootNode = mgr->getRootSceneNode()->createChildSceneNode(name, position);
    rootNode->setScale(length()/100.0, length()/100.0, length()/100.0);
    rootNode->attachObject(ent);
    // rootNode->setScale(.6, .6, .6);
    ent->setMaterialName("Tile/Rakan"); 
}

void AbstractCubester::simulate(const Ogre::Real elapsedTime)
{
    if(!inMotion)
    {
        direction = getAction();
        inMotion = true;
    }
    Ogre::Vector3 nowPos = rootNode->getPosition();
    if(direction == 0)
    {
        rootNode->setPosition(Ogre::Vector3(nowPos.x, nowPos.y, nowPos.z - moveSpeed() * elapsedTime));
        if(rootNode->getPosition().z < endPos.z)
        {
            // playerX -= 1;
            inMotion = false;
            return;
        }
    }
    else if(direction == 1)
    {
        rootNode->setPosition(Ogre::Vector3(nowPos.x + moveSpeed() * elapsedTime, nowPos.y, nowPos.z));
        if(rootNode->getPosition().x > endPos.x)
        {
            // playerY += 1;
            inMotion = false;
            return;
        }
    }
    else if(direction == 2)
    {
        rootNode->setPosition(Ogre::Vector3(nowPos.x, nowPos.y, nowPos.z + moveSpeed() * elapsedTime));
        if(rootNode->getPosition().z > endPos.z)
        {
            // playerX += 1;
            inMotion = false;
            return;
        }
    }
    else if(direction == 3)
    {
        rootNode->setPosition(Ogre::Vector3(nowPos.x - moveSpeed() * elapsedTime, nowPos.y, nowPos.z));
        if(rootNode->getPosition().x < endPos.x)
        {
            // playerY -= 1;
            inMotion = false;
            return;
        }
    }
}
int AbstractCubester::getX()
{
    return xIndex;
}
int AbstractCubester::getY()
{
    return yIndex;
}

int AbstractCubester::getAction()
{
    return 0;
}

int AbstractCubester::goUp()
{
    actionIndex++;
    endPos.z -= length();
    return 0;
}

int AbstractCubester::goRight()
{
    actionIndex++;
    endPos.x += length();
    return 1;
}

int AbstractCubester::goDown()
{
    actionIndex++;
    endPos.z += length();
    return 2;
}

int AbstractCubester::goLeft()
{
    actionIndex++;
    endPos.x -= length();
    return 3;
}

/*-----------------------------CubesterTLSquare----------------------------------*/
CubesterTLSquare::CubesterTLSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr;
    position = pos;
    endPos = position;
    xIndex = xInd;
    yIndex = yInd;
    pathLength = length;
    inMotion = false;
    actionIndex = 0;
}
CubesterTLSquare::~CubesterTLSquare()
{

}

int CubesterTLSquare::getAction()
{
    int caseNum = (actionIndex/pathLength) % 4;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goRight();
    else if(caseNum == 1)
        return goDown();
    else if(caseNum == 2)
        return goLeft();
    else if(caseNum == 3)
        return goUp();
}

/*-----------------------------CubesterTRSquare----------------------------------*/
CubesterTRSquare::CubesterTRSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr;
    position = pos;
    position.x += 50*length;
    endPos = position;
    xIndex = xInd;
    yIndex = yInd;
    pathLength = length;
    inMotion = false;
    actionIndex = 0;
}
CubesterTRSquare::~CubesterTRSquare()
{

}

int CubesterTRSquare::getAction()
{
    int caseNum = (actionIndex/pathLength) % 4;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goDown();
    else if(caseNum == 1)
        return goLeft();
    else if(caseNum == 2)
        return goUp();
    else if(caseNum == 3)
        return goRight();
}

/*-----------------------------CubesterBRSquare----------------------------------*/
CubesterBRSquare::CubesterBRSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr;
    position = pos;
    position.x += 50*length;
    position.z += 50*length;
    endPos = position;
    xIndex = xInd;
    yIndex = yInd;
    pathLength = length;
    inMotion = false;
    actionIndex = 0;
}
CubesterBRSquare::~CubesterBRSquare()
{

}

int CubesterBRSquare::getAction()
{
    int caseNum = (actionIndex/pathLength) % 4;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goLeft();
    else if(caseNum == 1)
        return goUp();
    else if(caseNum == 2)
        return goRight();
    else if(caseNum == 3)
        return goDown();
}

/*-----------------------------CubesterBLSquare----------------------------------*/
CubesterBLSquare::CubesterBLSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr;
    position = pos;
    position.z += 50*length;
    endPos = position;
    xIndex = xInd;
    yIndex = yInd;
    pathLength = length;
    inMotion = false;
    actionIndex = 0;
}
CubesterBLSquare::~CubesterBLSquare()
{

}

int CubesterBLSquare::getAction()
{
    int caseNum = (actionIndex/pathLength) % 4;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goUp();
    else if(caseNum == 1)
        return goRight();
    else if(caseNum == 2)
        return goDown();
    else if(caseNum == 3)
        return goLeft();
}



Cubester::Cubester(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length,  char t)
{
    std::string material = "Tile/Rakan";
    if(t == typeForCubesterTLSquare())
    {
        cubester = new CubesterTLSquare(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterTRSquare())
    {
        cubester = new CubesterTRSquare(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterBRSquare())
    {
        cubester = new CubesterBRSquare(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterBLSquare())
    {
        cubester = new CubesterBLSquare(sceneMgr, pos, xInd, yInd, length);
    }
    create(material);
}
Cubester::~Cubester()
{
    delete cubester;
}

void Cubester::create(std::string material)
{
    cubester->create(material);
}

void Cubester::simulate(const Ogre::Real elapsedTime)
{
    cubester->simulate(elapsedTime);
}

Ogre::Vector3 Cubester::getPosition()
{
    return cubester->getPosition();
}