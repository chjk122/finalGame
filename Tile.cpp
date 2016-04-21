#include "Tile.h"

bool AbstractTile::getIsWalkable()
{
    return isWalkable;
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

    //translates the tile to the given position
    btTransform tile;
    tile.setIdentity();
    tile.setOrigin(btVector3(position.x, position.y, position.z));

    //add the entity to a new child node
    Ogre::Entity* entity = mgr->createEntity(name); 
    Ogre::SceneNode* childNode = mgr->getRootSceneNode()->createChildSceneNode(name);
    childNode->attachObject(entity);
    entity->setMaterialName("Examples/Rocky"); 
    entity->setCastShadows(false);
}
/*-----------------------------OutterTile----------------------------------*/
OutterTile::OutterTile(Ogre::SceneManager* sceneMgr, 
                       Ogre::Vector3 pos, int xInd, int yInd)
{
    mgr = sceneMgr;
    position = pos;
    xIndex = xInd;
    yIndex = yInd;
    isWalkable = false;
}

OutterTile::~OutterTile()
{

}

void OutterTile::create()
{

    // creates the tile on the ground plane
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0.0);
    Ogre::Vector3 up = Ogre::Vector3::UNIT_Z;
    std::string name = xIndex + "y" + yIndex;
    Ogre::MeshManager::getSingleton().createPlane(name, 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
        AbstractTile::length(),AbstractTile::length(),20,20,true,1,5,5,up);

    //translates the tile to the given position
    btTransform tile;
    tile.setIdentity();
    tile.setOrigin(btVector3(position.x, position.y, position.z));

    //add the entity to a new child node
    Ogre::Entity* entity = mgr->createEntity(name); 
    Ogre::SceneNode* childNode = mgr->getRootSceneNode()->createChildSceneNode(name);
    childNode->attachObject(entity);
    entity->setMaterialName("Examples/GrassFloor"); 
    entity->setCastShadows(false);
}

Tile::Tile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, char t)
{
    //if type == whatever
    //tile = new <INSERT TILE TYPE>
}
Tile::~Tile()
{

}

void Tile::create()
{
    tile->create();
}

bool Tile::getIsWalkable()
{
    return tile->getIsWalkable();
}