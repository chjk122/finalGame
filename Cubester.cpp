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

double AbstractCubester::moveSpeed()
{
    return 135;
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
    ent->setMaterialName(material); 
    startPosition = position;
}

void AbstractCubester::simulate(const Ogre::Real elapsedTime, Ogre::Vector3 playerPos)
{
    if(!inMotion)
    {
        direction = getAction(playerPos);
        if(direction != -1)
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

int AbstractCubester::getAction(Ogre::Vector3 playerPos)
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

int AbstractCubester::move(int dir)
{
    if(dir == 0 ) // 0 to pathLength go right
        return goUp();
    else if(dir == 1)
        return goRight();
    else if(dir == 2)
        return goDown();
    else if(dir == 3)
        return goLeft();
}

/*-----------------------------CubesterTLSquare----------------------------------*/
CubesterTLSquare::CubesterTLSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterTLSquare::~CubesterTLSquare(){}

int CubesterTLSquare::getAction(Ogre::Vector3 playerPos)
{
    int dir = (actionIndex/pathLength) % 4;

    if(dir == 0 ) // 0 to pathLength go right
        return goRight();
    else if(dir == 1)
        return goDown();
    else if(dir == 2)
        return goLeft();
    else if(dir == 3)
        return goUp();
}

/*-----------------------------CubesterTRSquare----------------------------------*/
CubesterTRSquare::CubesterTRSquare(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length)
{
    mgr = sceneMgr; position = pos; position.x += 50*length;
    endPos = position; pathLength = length; inMotion = false; actionIndex = 0;
}
CubesterTRSquare::~CubesterTRSquare(){}

int CubesterTRSquare::getAction(Ogre::Vector3 playerPos)
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

int CubesterBRSquare::getAction(Ogre::Vector3 playerPos)
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

int CubesterBLSquare::getAction(Ogre::Vector3 playerPos)
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

int CubesterCCTLSquare::getAction(Ogre::Vector3 playerPos)
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

int CubesterCCTRSquare::getAction(Ogre::Vector3 playerPos)
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

int CubesterCCBRSquare::getAction(Ogre::Vector3 playerPos)
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

int CubesterCCBLSquare::getAction(Ogre::Vector3 playerPos)
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

int CubesterTBLine::getAction(Ogre::Vector3 playerPos)
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

int CubesterBTLine::getAction(Ogre::Vector3 playerPos)
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

int CubesterLRLine::getAction(Ogre::Vector3 playerPos)
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

int CubesterRLLine::getAction(Ogre::Vector3 playerPos)
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

int CubesterTTP::getAction(Ogre::Vector3 playerPos)
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

int CubesterBTP::getAction(Ogre::Vector3 playerPos)
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

int CubesterRTP::getAction(Ogre::Vector3 playerPos)
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

int CubesterLTP::getAction(Ogre::Vector3 playerPos)
{
    int caseNum = (actionIndex/pathLength) % 2;
    if(caseNum == 0 ) // 0 to pathLength go right
        return goRight();
    else
        reload();
}


CubesterChase::CubesterChase(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int distance)
{
    startPosition = pos; 
    mgr = sceneMgr;
    position = pos;
    endPos = position;
    pathLength = distance; 

}
CubesterChase::~CubesterChase(){}

int CubesterChase::getAction(Ogre::Vector3 playerPos){
    position = rootNode->getPosition();

    int distanceFromPlayer = Ogre::Math::Sqrt(Ogre::Math::Pow((startPosition.x - playerPos.x),2) + Ogre::Math::Pow((startPosition.z - playerPos.z),2));

    if(distanceFromPlayer <= pathLength ){

        return moveTowardsPos(playerPos);
    }
    else if(position != startPosition){
        return moveTowardsPos(startPosition);
    }
    else{
        return -1;
    }

}

int CubesterChase::moveTowardsPos(Ogre::Vector3 pos){

    bool closerToX = (abs(pos.x - position.x) > abs(pos.z - position.z)) && ((abs(Ogre::Math::Ceil(pos.x)) - abs(Ogre::Math::Ceil(position.x))) != 0) ;
    bool closerToZ = (abs(pos.x - position.x) < abs(pos.z - position.z))  && ((abs(Ogre::Math::Ceil(pos.z)) - abs(Ogre::Math::Ceil(position.z))) != 0);
    //is it closer on the X axis? Okay cool, choose left or right and go that way
    if(closerToX){
        std::cout <<"CLOSER TO X" << std::endl;
        //left
        if (pos.x < position.x ){
        
            return(move(3));
        
        }
        //right
        else if (pos.x > position.x ){
            
            return(move(1));
            
        }
    }
    if (closerToZ){
        //down
                std::cout <<"CLOSER TO Z" << std::endl;

        if(pos.z > position.z ){
            return(move(2)); 

        }
        //up
        else if (pos.z < position.z ){
            return(move(0)); 
        }
    }
    //if they're equal, do some random mumbo jumbo
    else{
                std::cout <<"TO BOTH" << std::endl;

        if (pos.x < position.x ){

            if(pos.z > position.z){
                return((int)rand()%2 ? move(2) : move(3)); 

            }
            else if (pos.z < position.z ){
                return((int)rand()%2 ? move(0) : move(3)); 

            }
            else{
                return(move(3));
            }
        }

        else if (pos.x > position.x ){
            if(pos.z > position.z ){
                return((int)rand()%2 ? move(2) : move(1)); 

            }
            else if (pos.z < position.z ){
                return((int)rand()%2 ? move(0) : move(1)); 

            }
            else{
                return(move(1));
            }
        }
        else if(pos.z > position.z ){
            return(move(2)); 

        }
        else if (pos.z < position.z ){
            return(move(0)); 
        }


    }
}




Cubester::Cubester(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, int length,  char t)
{
    std::string material = "Cubester/Normal";
    if(t == typeForCubesterTLSquare())
    {
        cubester = new CubesterTLSquare(sceneMgr, pos, xInd, yInd, length);
        material = "Cubester/Square";
    }
    else if(t == typeForCubesterTRSquare())
    {
        cubester = new CubesterTRSquare(sceneMgr, pos, xInd, yInd, length);
        material = "Cubester/Square";
    }
    else if(t == typeForCubesterBRSquare())
    {
        cubester = new CubesterBRSquare(sceneMgr, pos, xInd, yInd, length);
        material = "Cubester/Square";
    }
    else if(t == typeForCubesterBLSquare())
    {
        cubester = new CubesterBLSquare(sceneMgr, pos, xInd, yInd, length);
        material = "Cubester/Square";
    }
    else if(t == typeForCubesterCCTLSquare())
    {
        cubester = new CubesterCCTLSquare(sceneMgr, pos, xInd, yInd, length);
        material = "Cubester/Square";
    }
    else if(t == typeForCubesterCCTRSquare())
    {
        cubester = new CubesterCCTRSquare(sceneMgr, pos, xInd, yInd, length);
        material = "Cubester/Square";
    }
    else if(t == typeForCubesterCCBRSquare())
    {
        cubester = new CubesterCCBRSquare(sceneMgr, pos, xInd, yInd, length);
        material = "Cubester/Square";
    }
    else if(t == typeForCubesterCCBLSquare())
    {
        cubester = new CubesterCCBLSquare(sceneMgr, pos, xInd, yInd, length);
        material = "Cubester/Square";
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
        material = "Cubester/Teleport";
    }
    else if(t == typeForCubesterBTP())
    {
        cubester = new CubesterBTP(sceneMgr, pos, xInd, yInd, length);
        material = "Cubester/Teleport";
    }
    else if(t == typeForCubesterRTP())
    {
        cubester = new CubesterRTP(sceneMgr, pos, xInd, yInd, length);
        material = "Cubester/Teleport";
    }
    else if(t == typeForCubesterLTP())
    {
        cubester = new CubesterLTP(sceneMgr, pos, xInd, yInd, length);
        material = "Cubester/Teleport";
    }
    else if(t == typeForCubesterChase())
    {
        cubester = new CubesterChase(sceneMgr, pos, xInd, yInd, length*50);
        material = "Cubester/Teleport";
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
void Cubester::simulate(const Ogre::Real elapsedTime, Ogre::Vector3 playerPos)
{
    cubester->simulate(elapsedTime, playerPos);
}

Ogre::Vector3 Cubester::getPosition()
{
    return cubester->getPosition();
}