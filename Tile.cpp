#include "Tile.h"

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
    // creates the tile on the ground plane
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0.0);
    Ogre::Vector3 up = Ogre::Vector3::UNIT_Z;
    std::string name = xIndex + "y" + yIndex;
    Ogre::MeshManager::getSingleton().createPlane(name, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
        AbstractTile::length(),AbstractTile::length(),20,20,true,1,5,5,up);

    //add the entity to a new child node
    Ogre::Entity* entity = mgr->createEntity(name); 
    Ogre::SceneNode* childNode = mgr->getRootSceneNode()->createChildSceneNode();
    childNode->attachObject(entity);
    childNode->setPosition(Ogre::Vector3(position.x, position.y, position.z));
    entity->setMaterialName("Examples/Rocky"); 
    entity->setCastShadows(true);
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

    // creates the tile on the ground plane
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0.0);
    Ogre::Vector3 up = Ogre::Vector3::UNIT_Z;
    std::string name = xIndex + "y" + yIndex;
    Ogre::MeshManager::getSingleton().createPlane(name, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
        AbstractTile::length(),AbstractTile::length(),20,20,true,1,5,5,up);

    //add the entity to a new child node
    Ogre::Entity* entity = mgr->createEntity(name); 
    Ogre::SceneNode* childNode = mgr->getRootSceneNode()->createChildSceneNode();
    childNode->attachObject(entity);
    childNode->setPosition(Ogre::Vector3(position.x, position.y, position.z));
    entity->setMaterialName("Examples/GrassFloor"); 
    entity->setCastShadows(true);
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