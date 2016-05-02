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
    return rootNode->getPosition();
}
void AbstractCubester::create(std::string material)
{
    Ogre::MeshManager::getSingleton().create("cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    ent = mgr->createEntity(Ogre::MeshManager::getSingleton().getByName(
        "cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));
    name = patch::to_string((int)(position.x)) + "enemy" + patch::to_string((int)(position.z));
    Ogre::Vector3 newPos(position.x, position.y + length()/2, position.z);
    position = newPos;
    endPos = newPos;
    rootNode = mgr->getRootSceneNode()->createChildSceneNode(name, position);
    rootNode->setScale(length()/100.0, length()/100.0, length()/100.0);
    rootNode->attachObject(ent);
    // rootNode->setScale(.6, .6, .6);
    ent->setMaterialName("Cubester/Normal"); 
    startPosition = position;
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
            rootNode->setPosition(endPos);
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
            rootNode->setPosition(endPos);
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
            rootNode->setPosition(endPos);
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
            rootNode->setPosition(endPos);
            // playerY -= 1;
            inMotion = false;
            return;
        }
    }
}

void AbstractCubester::reload()
{
    position = startPosition;
    rootNode->setPosition(position);
    endPos = position;
    actionIndex = 0;
    inMotion = false;
}

Ogre::SceneNode * AbstractCubester::getNode()
{
    return rootNode;
}

std::string AbstractCubester::getName()
{
    return name;
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
    mgr = sceneMgr; position = pos;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterTLSquare::~CubesterTLSquare(){}

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
    mgr = sceneMgr; position = pos; position.x += 50*length;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterTRSquare::~CubesterTRSquare(){}

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
    mgr = sceneMgr; position = pos; position.x += 50*length; position.z += 50*length;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterBRSquare::~CubesterBRSquare(){}

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
    mgr = sceneMgr; position = pos; position.z += 50*length;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterBLSquare::~CubesterBLSquare(){}

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

//*-------------------------------------CounterClockwise Square Cubester-----------------------------*//

CubesterCCTLSquare::CubesterCCTLSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterCCTLSquare::~CubesterCCTLSquare(){}

int CubesterCCTLSquare::getAction()
{
    int caseNum = (actionIndex/pathLength) % 4;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goDown();
    else if(caseNum == 1)
        return goRight();
    else if(caseNum == 2)
        return goUp();
    else if(caseNum == 3)
        return goLeft();
}

CubesterCCTRSquare::CubesterCCTRSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos; position.x += 50*length;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterCCTRSquare::~CubesterCCTRSquare(){}

int CubesterCCTRSquare::getAction()
{
    int caseNum = (actionIndex/pathLength) % 4;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goLeft();
    else if(caseNum == 1)
        return goDown();
    else if(caseNum == 2)
        return goRight();
    else if(caseNum == 3)
        return goUp();
}

CubesterCCBRSquare::CubesterCCBRSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos; position.x += 50*length; position.z += 50*length;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterCCBRSquare::~CubesterCCBRSquare(){}

int CubesterCCBRSquare::getAction()
{
    int caseNum = (actionIndex/pathLength) % 4;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goUp();
    else if(caseNum == 1)
        return goLeft();
    else if(caseNum == 2)
        return goDown();
    else if(caseNum == 3)
        return goRight();
}

CubesterCCBLSquare::CubesterCCBLSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos; position.z += 50*length;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterCCBLSquare::~CubesterCCBLSquare(){}

int CubesterCCBLSquare::getAction()
{
    int caseNum = (actionIndex/pathLength) % 4;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goRight();
    else if(caseNum == 1)
        return goUp();
    else if(caseNum == 2)
        return goLeft();
    else if(caseNum == 3)
        return goDown();
}

//*-------------------------------------Line Cubester-----------------------------*//
CubesterTBLine::CubesterTBLine(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos; 
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterTBLine::~CubesterTBLine(){}

int CubesterTBLine::getAction()
{
    int caseNum = (actionIndex/pathLength) % 2;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goDown();
    else
        return goUp();
}

CubesterBTLine::CubesterBTLine(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos; position.z += 50*length;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterBTLine::~CubesterBTLine(){}

int CubesterBTLine::getAction()
{
    int caseNum = (actionIndex/pathLength) % 2;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goUp();
    else
        return goDown();
}

CubesterLRLine::CubesterLRLine(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterLRLine::~CubesterLRLine(){}

int CubesterLRLine::getAction()
{
    int caseNum = (actionIndex/pathLength) % 2;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goRight();
    else
        return goLeft();
}

CubesterRLLine::CubesterRLLine(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos; position.x += 50*length;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterRLLine::~CubesterRLLine(){}

int CubesterRLLine::getAction()
{
    int caseNum = (actionIndex/pathLength) % 2;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goLeft();
    else
        return goRight();
}

//*-------------------------------------Teleport Cubester-----------------------------*//
CubesterTTP::CubesterTTP(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterTTP::~CubesterTTP(){}

int CubesterTTP::getAction()
{
    int caseNum = (actionIndex/pathLength) % 2;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goDown();
    else
        reload();
}

CubesterBTP::CubesterBTP(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos; position.z += length*50;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterBTP::~CubesterBTP(){}

int CubesterBTP::getAction()
{
    int caseNum = (actionIndex/pathLength) % 2;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goUp();
    else
        reload();
}

CubesterRTP::CubesterRTP(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos; position.x += length*50;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterRTP::~CubesterRTP(){}

int CubesterRTP::getAction()
{
    int caseNum = (actionIndex/pathLength) % 2;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goLeft();
    else
        reload();
}

CubesterLTP::CubesterLTP(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterLTP::~CubesterLTP(){}

int CubesterLTP::getAction()
{
    int caseNum = (actionIndex/pathLength) % 2;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goRight();
    else
        reload();
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
    else if(t == typeForCubesterCCTLSquare())
    {
        cubester = new CubesterCCTLSquare(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterCCTRSquare())
    {
        cubester = new CubesterCCTRSquare(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterCCBRSquare())
    {
        cubester = new CubesterCCBRSquare(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterCCBLSquare())
    {
        cubester = new CubesterCCBLSquare(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterTBLine())
    {
        cubester = new CubesterTBLine(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterBTLine())
    {
        cubester = new CubesterBTLine(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterLRLine())
    {
        cubester = new CubesterLRLine(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterRLLine())
    {
        cubester = new CubesterRLLine(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterTTP())
    {
        cubester = new CubesterTTP(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterBTP())
    {
        cubester = new CubesterBTP(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterRTP())
    {
        cubester = new CubesterRTP(sceneMgr, pos, xInd, yInd, length);
    }
    else if(t == typeForCubesterLTP())
    {
        cubester = new CubesterLTP(sceneMgr, pos, xInd, yInd, length);
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

void Cubester::reload()
{
    cubester->reload();
}

Ogre::SceneNode * Cubester::getNode()
{
    return cubester->getNode();
}

std::string Cubester::getName()
{
    return cubester->getName();
}
void Cubester::simulate(const Ogre::Real elapsedTime)
{
    cubester->simulate(elapsedTime);
}

Ogre::Vector3 Cubester::getPosition()
{
    return cubester->getPosition();
}