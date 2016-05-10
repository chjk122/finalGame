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

bool AbstractTile::getIsWalkable(Player* p)
{
    return isWalkable;
}

Ogre::Vector3 AbstractTile::getPosition()
{
    return position;
}

void AbstractTile::reload()
{
}

void AbstractTile::setNeighbors(AbstractTile *u, AbstractTile *r, AbstractTile *d, AbstractTile *l)
{
    up = u;
    right = r;
    down = d;
    left = l;
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
    ent = mgr->createEntity(Ogre::MeshManager::getSingleton().getByName(
     "cube.mesh", 
     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));
    Ogre::Vector3 newPos(position.x, position.y - (length()/2), position.z);
    Ogre::SceneNode* rootNode = mgr->getRootSceneNode()->createChildSceneNode(name, newPos);
    rootNode->setScale(length()/100.0, length()/100.0, length()/100.0);
    rootNode->attachObject(ent);
    // rootNode->setScale(.6, .6, .6); 
    ent->setMaterialName(material);
}

void PathTile::event(Player* p)
{
    p->breath();
}

/*------------------------------------BloodPathTile ------------------------------------------*/
BloodPathTile::BloodPathTile(Ogre::SceneManager* sceneMgr, 
                   Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
BloodPathTile::~BloodPathTile()
{

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
    Mix_Chunk* chunk;
    chunk = Mix_LoadWAV("Music/0/win.wav");
    Mix_PlayChannel( -1, chunk, 0 );
    p->levelFinished = true;
}

/*-----------------------------SpikeTile----------------------------------*/
SpikeTile::SpikeTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{
   
}

SpikeTile::~SpikeTile()
{

}
void SpikeTile::event(Player* p)
{
    p->breath();
    p->damageTaken(Player::spikeDamage());
    Mix_Chunk* chunk;
    chunk = Mix_LoadWAV("Music/0/spike.wav");
    Mix_PlayChannel( -1, chunk, 0 );
    if(p->health <=0)
    {
        p->kill("Cube/deathSpike");
    }
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
    p->breath();
    p->burn = 5;
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
    Mix_Chunk* chunk;
    chunk = Mix_LoadWAV("Music/0/poison.wav");
    Mix_PlayChannel( -1, chunk, 0 );
    p->breath();
    p->poison = true;
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
    p->breath();
    Ogre::Vector3 pos = p->endPos;
    if(p->direction == 0 && up != NULL && up->getIsWalkable(p))
    {
        p->move(0, Ogre::Vector3(pos.x, pos.y , pos.z-50));
    }
    else if(p->direction == 1 && right != NULL && right->getIsWalkable(p))
    { 
        p->move(1, Ogre::Vector3(pos.x+50, pos.y , pos.z));
    }
    else if(p->direction == 2 && down != NULL && down->getIsWalkable(p))
    {
        p->move(2, Ogre::Vector3(pos.x, pos.y , pos.z+50));
    }
    else if(p->direction == 3 && left != NULL && left->getIsWalkable(p))
    {
        p->move(3, Ogre::Vector3(pos.x-50, pos.y , pos.z));
    }
}
//*------------------------------------Directional TIles--------------------------------------*//
/*-----------------------------DUpTile----------------------------------*/
DUpTile::DUpTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
DUpTile::~DUpTile()
{

}
void DUpTile::event(Player* p)
{
    p->breath();
    Ogre::Vector3 pos = p->endPos;
    p->move(0, Ogre::Vector3(pos.x, pos.y , pos.z-50)); 
}
/*-----------------------------DDownTile----------------------------------*/
DDownTile::DDownTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
DDownTile::~DDownTile()
{

}
void DDownTile::event(Player* p)
{
    p->breath();
    Ogre::Vector3 pos = p->endPos;
    p->move(2, Ogre::Vector3(pos.x, pos.y , pos.z+50)); 
}

/*-----------------------------DLeftTile----------------------------------*/
DLeftTile::DLeftTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
DLeftTile::~DLeftTile()
{

}
void DLeftTile::event(Player* p)
{
    p->breath();
    Ogre::Vector3 pos = p->endPos;
    p->move(3, Ogre::Vector3(pos.x-50, pos.y , pos.z)); 
}

/*-----------------------------DRightTile----------------------------------*/
DRightTile::DRightTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
DRightTile::~DRightTile()
{

}
void DRightTile::event(Player* p)
{
    p->breath();
    Ogre::Vector3 pos = p->endPos;
    p->move(1, Ogre::Vector3(pos.x+50, pos.y , pos.z)); 
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
    p->oxygenLost(1);
    p->removeBurn();
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
    p->breath();
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
    p->breath();
}

/*-----------------------------CureTile----------------------------------*/
CureTile::CureTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
CureTile::~CureTile()
{

}

void CureTile::event(Player* p)
{
    if(p->poison == true)
    {
        Mix_Chunk* chunk;
        chunk = Mix_LoadWAV("Music/0/cure.wav");
        Mix_PlayChannel( -1, chunk, 0 );
    }
    p->breath();
    p->poison = false;
}

/*-----------------------------DoorTile----------------------------------*/
DoorTile::DoorTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{
     isWalkable = false;
     unlocked = false;
}
DoorTile::~DoorTile()
{
    
}

void DoorTile::reload()
{
    ent->setMaterialName("Tile/DoorLocked");
    unlocked = false;
}

void DoorTile::event(Player* p)
{
    p->breath();
}

bool DoorTile::getIsWalkable(Player *p)
{
    if(unlocked)
        return true;
    else if(p->hasKey()) 
    {
        Mix_Chunk* chunk;
        chunk = Mix_LoadWAV("Music/0/unlock.wav");
        Mix_PlayChannel( -1, chunk, 0 );
        unlocked = true;
        p->usedKey();
        ent->setMaterialName("Tile/DoorUnlocked");
        return true;
    }
    else
        return false;
}

/*-----------------------------KeyTile----------------------------------*/
KeyTile::KeyTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{
    takenKey = false;
}
KeyTile::~KeyTile()
{
    
}

void KeyTile::reload()
{
    ent->setMaterialName("Tile/Key");
    takenKey = false;
}


void KeyTile::event(Player* p)
{
    ent->setMaterialName("Tile/Path");
    p->breath();
    if(!takenKey)
    {
        Mix_Chunk* chunk;
        chunk = Mix_LoadWAV("Music/0/key.wav");
        Mix_PlayChannel( -1, chunk, 0 );
        p->gotKey();
        takenKey = true;
    }
}

/*-----------------------------BloodKeyTile----------------------------------*/
BloodKeyTile::BloodKeyTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
KeyTile(sceneMgr, pos, xInd, yInd)
{
}
BloodKeyTile::~BloodKeyTile()
{
    
}

void BloodKeyTile::reload()
{
    ent->setMaterialName("Tile/BloodKey");
    takenKey = false;
}


void BloodKeyTile::event(Player* p)
{
    ent->setMaterialName("Tile/BloodPath");
    p->breath();
    if(!takenKey)
    {
        Mix_Chunk* chunk;
        chunk = Mix_LoadWAV("Music/0/key.wav");
        Mix_PlayChannel( -1, chunk, 0 );
        p->gotKey();
        takenKey = true;
    }
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
    p->breath();
    p->changeMaterial("Tile/Rakan");
}

/*----------------------------Grass Tile-------------------------------------*/
SpaceTile::SpaceTile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}

SpaceTile::~SpaceTile()
{

}
void SpaceTile::event(Player* p)
{
    p->breath();
    p->changeMaterial("Tile/mineGrass");
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
}

/*-----------------------------LetterTile----------------------------------*/
LetterTile::LetterTile(Ogre::SceneManager* sceneMgr, 
                   Ogre::Vector3 pos, int xInd, int yInd):
PathTile(sceneMgr, pos, xInd, yInd)
{

}
LetterTile::~LetterTile()
{

}

Tile::Tile(Ogre::SceneManager* sceneMgr, Ogre::Vector3 pos, int xInd, int yInd, char t, int mode)
{
    std::string material = "Tile/Path";
    if(t == typeForOuterTile())
    {
        tile = new OuterTile(sceneMgr, pos, xInd, yInd);
        if(mode == 0)
        {
            material = "Tile/Outer";
        }
        else if(mode >= 7 && mode <= 9)
        {
            material = "Tile/mineDirt";
        }
    }
    else if(t == typeForPathTile())
    {
        tile = new PathTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Path";
    }
    else if(t == typeForBloodPathTile())
    {
        tile = new BloodPathTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/BloodPath";
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
        if(mode == 0)
        {
            material = "Tile/Ice";
        }
        else if(mode >= 7 && mode <= 9)
        {
            material = "Tile/mineIce";
        }
    }
    else if(t == typeForDUpTile())
    {
        tile = new DUpTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/longHorn";
    }
    else if(t == typeForDDownTile())
    {
        tile = new DDownTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/longHorn";
    }
    else if(t == typeForDLeftTile())
    {
        tile = new DLeftTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/longHorn";
    }
    else if(t == typeForDRightTile())
    {
        tile = new DRightTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/longHorn";
    }
    else if(t == typeForSlowTile())
    {
        tile = new SlowTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Jinx";
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
        material = "Tile/DoorLocked";
    }
    else if(t == typeForKeyTile())
    {
        tile = new KeyTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Key";
    }
    else if(t == typeForBloodKeyTile())
    {
        tile = new BloodKeyTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/BloodKey";
    }
    else if(t == typeForRakanTile())
    {
        tile = new RakanTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Rakan";
    }
    else if(t == typeForSpikeTile())
    {
        tile = new SpikeTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/Spike";
    }
    else if(t == typeForCureTile())
    {
        tile = new CureTile(sceneMgr, pos, xInd, yInd);
        material = "Item/Cure";
    }
    else if(t == typeForSpaceTile())
    {
        tile = new SpaceTile(sceneMgr, pos, xInd, yInd);
        material = "Tile/mineGrass";
    }
    else if(t >= typeForATile() && t <= typeForZTile())
    {
        tile = new LetterTile(sceneMgr, pos, xInd, yInd);
        if(mode == 7)
        {
            material = "Tile/mineLava/"  + patch::to_string(t);
        }
        else if(mode == 8)
        {
            material = "Tile/mineWater/"  + patch::to_string(t);
        }
        else if(mode == 9)
        {
            material = "Tile/mineDirt/"  + patch::to_string(t);
        }

        
        // if(mode == 1,2,3)
        // Lava
        // water
        // dirt

    }
    // float iSecret = rand() % 10 + 1;
    // if(iSecret < 5)
    //     material = "Tile/Rakan";
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

void Tile::reload()
{
    tile->reload();
}

bool Tile::getIsWalkable(Player *p)
{
    return tile->getIsWalkable(p);
}

Ogre::Vector3 Tile::getPosition()
{
    return tile->getPosition();
}

void Tile::event(Player* p)
{
     tile->event(p);
}

void Tile::setNeighbors(Tile *u, Tile *r, Tile *d, Tile *l)
{
     tile->setNeighbors(u->tile, r->tile, d->tile, l->tile);
}