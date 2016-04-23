#include "Tile.h"

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

bool AbstractTile::getIsWalkable()
{
    return isWalkable;
}

Ogre::Vector3 AbstractTile::getPosition()
{
    return position;
}

/*------------------------------------PathTile ------------------------------------------*/
PathTile::PathTile(Ogre::SceneManager* sceneMgr, 
                   Ogre::Vector3 pos, int xInd, int yInd)
{
    mgr = sceneMgr;
    position = pos;
    xIndex = xInd;
    yIndex = yInd;
    isWalkable = true;
}
PathTile::~PathTile()
{

}

void PathTile::create()
{
    std::string name = patch::to_string(xIndex) + "y" + patch::to_string(yIndex);
    Ogre::MeshManager::getSingleton().create("cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::Entity* entity = mgr->createEntity(Ogre::MeshManager::getSingleton().getByName(
     "cube.mesh", 
     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));
    Ogre::Vector3 newPos(position.x, position.y - (length()/2), position.z);
    Ogre::SceneNode* rootNode = mgr->getRootSceneNode()->createChildSceneNode(name, newPos);
    rootNode->setScale(length()/100.0, length()/100.0, length()/100.0);
    rootNode->attachObject(entity);
    // rootNode->setScale(.6, .6, .6);
    entity->setMaterialName("Tile/Path"); 
}
/*-----------------------------StartTile----------------------------------*/
StartTile::StartTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
StartTile::~StartTile()
{

}

/*-----------------------------OuterTile----------------------------------*/
OuterTile::OuterTile(Ogre::SceneManager* sceneMgr, 
                       Ogre::Vector3 pos, int xInd, int yInd)
{
    mgr = sceneMgr;
    position = pos;
    xIndex = xInd;
    yIndex = yInd;
    isWalkable = false;
}

OuterTile::~OuterTile()
{

}

void OuterTile::create()
{
    std::string name = patch::to_string(xIndex) + "y" + patch::to_string(yIndex);
    Ogre::MeshManager::getSingleton().create("cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::Entity* entity = mgr->createEntity(Ogre::MeshManager::getSingleton().getByName(
     "cube.mesh", 
     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));
    Ogre::Vector3 newPos(position.x, position.y - (length()/2), position.z);
    Ogre::SceneNode* rootNode = mgr->getRootSceneNode()->createChildSceneNode(name, newPos);
    rootNode->setScale(length()/100.0, length()/100.0, length()/100.0);
    rootNode->attachObject(entity);
    // rootNode->setScale(.6, .6, .6);
    entity->setMaterialName("Tile/Outer");
}

Tile::Tile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, char t)
{
    if(t == typeForOuterTile())
    {
        tile = new OuterTile(sceneMgr, pos, xInd, yInd);
    }
    else if(t == typeForPathTile())
    {
        tile = new PathTile(sceneMgr, pos, xInd, yInd);
    }
    else if(t == typeForStartTile())
    {
        tile = new StartTile(sceneMgr, pos, xInd, yInd);
    }
    // else if(t == typeForFinishTile())
    // {
    //     tile = new StartTile(sceneMgr, pos, xInd, yInd);
    // }

    tile->create();
    //if type == whatever
    //tile = new <INSERT TILE TYPE>
}
Tile::~Tile()
{
    delete tile;
}

void Tile::create()
{
    tile->create();
}

bool Tile::getIsWalkable()
{
    return tile->getIsWalkable();
}

Ogre::Vector3 Tile::getPosition()
{
    return tile->getPosition();
}