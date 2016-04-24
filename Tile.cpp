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

void PathTile::create(std::string material)
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
    entity->setMaterialName(material);
}

void PathTile::event(Player* p)
{
    printf("%i yindex %i\n", xIndex, yIndex );
}
/*-----------------------------StartTile----------------------------------*/
StartTile::StartTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
StartTile::~StartTile()
{

}

/*-----------------------------FinishTile----------------------------------*/
FinishTile::FinishTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
FinishTile::~FinishTile()
{

}

void FinishTile::event(Player* p)
{
    printf("Finish\n");
}


/*-----------------------------LavaTile----------------------------------*/
LavaTile::LavaTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{
   
}

LavaTile::~LavaTile()
{

}
void LavaTile::event(Player* p)
{
    printf("Lava");
}

/*-----------------------------PoisonTile----------------------------------*/
PoisonTile::PoisonTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
PoisonTile::~PoisonTile()
{

}

void PoisonTile::event(Player* p)
{
    p->health -= 5;
    printf("%i health\n", p->health);
}

/*-----------------------------IceTile----------------------------------*/
IceTile::IceTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
IceTile::~IceTile()
{

}

void IceTile::event(Player* p)
{
    printf("IceTile");
}

/*-----------------------------WaterTile----------------------------------*/
WaterTile::WaterTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
WaterTile::~WaterTile()
{

}

void WaterTile::event(Player* p)
{
    printf("WaterTile");
}

/*-----------------------------TeleportTile----------------------------------*/
TeleportTile::TeleportTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
TeleportTile::~TeleportTile()
{

}

void TeleportTile::event(Player* p)
{
    printf("TeleportTile");
}

/*-----------------------------SlowTile----------------------------------*/
SlowTile::SlowTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
SlowTile::~SlowTile()
{

}

void SlowTile::event(Player* p)
{
    printf("SlowTile");
}

/*-----------------------------DoorTile----------------------------------*/
DoorTile::DoorTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
DoorTile::~DoorTile()
{
    
}

void DoorTile::event(Player* p)
{
    printf("DoorTile");
}

/*-----------------------------RakanTile----------------------------------*/
RakanTile::RakanTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}

RakanTile::~RakanTile()
{

}
void RakanTile::event(Player* p)
{
    p->changeMaterial("Tile/Rakan");
    printf("RakanTile");
}


/*-----------------------------OuterTile----------------------------------*/
OuterTile::OuterTile(Ogre::SceneManager* sceneMgr, 
                       Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{
    isWalkable = false;
}

OuterTile::~OuterTile()
{

}

void OuterTile::event(Player* p)
{
    printf("OuterTile\n");
}

Tile::Tile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, char t)
{
    std::string material = "Tile/Path";
    if(t == typeForOuterTile())
    {
        tile = new OuterTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Outer";
    }
    else if(t == typeForPathTile())
    {
        tile = new PathTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Path";
    }
    else if(t == typeForFinishTile())
    {
        tile = new FinishTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Finish";
    }
    else if(t == typeForStartTile())
    {
        tile = new StartTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Start";
    }
    else if(t == typeForLavaTile())
    {
        tile = new LavaTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Lava";
    }
     else if(t == typeForIceTile())
    {
        tile = new IceTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Ice";
    }
     else if(t == typeForSlowTile())
    {
        tile = new SlowTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Slow";
    }
     else if(t == typeForWaterTile())
    {
        tile = new WaterTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Water";
    }
     else if(t == typeForPoisonTile())
    {
        tile = new PoisonTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Poison";
    }
     else if(t == typeForTeleportTile())
    {
        tile = new TeleportTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Teleport";
    }
    else if(t == typeForDoorTile())
    {
        tile = new DoorTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Door";
    }
    else if(t == typeForRakanTile())
    {
        tile = new RakanTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Rakan";
    }

    create(material);
    //if type == whatever
    //tile = new <INSERT TILE TYPE>
}
Tile::~Tile()
{
    delete tile;
}

void Tile::create(std::string material)
{
    tile->create(material);
}

bool Tile::getIsWalkable()
{
    return tile->getIsWalkable();
}

Ogre::Vector3 Tile::getPosition()
{
    return tile->getPosition();
}

void Tile::event(Player* p)
{
     tile->event(p);
}