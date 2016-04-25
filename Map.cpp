#include "Map.h"

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

Map::Map(Player *play, Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos, std::vector< std::vector<Tile *> > v)
{
	
}

Map::Map(Player *play, Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos,
		 std::vector< std::string > v, std::vector< std::string > e):
mgr(sceneMgr), player(play)
{
	Tile *temp;
	Ogre::Vector3 pos(centerOfTopleftTilePos.x, centerOfTopleftTilePos.y, centerOfTopleftTilePos.z);
	for(int x = 0; x < v.size(); x++)
	{
		map.push_back(std::vector<Tile *>());
		for(int y = 0; y < v.size(); y++)
		{
			// code for the tiles
			temp = new Tile(mgr,pos, x, y, v[x][y]);
			map[x].push_back(temp);
			if(v[x][y] == Tile::typeForStartTile())
			{
				player->setPlayerCord(x,y, AbstractTile::length(), centerOfTopleftTilePos.z, centerOfTopleftTilePos.x);
			}
			//code for enemy locations
			if(e[x][y] != 'x')
			{
				//know it should be part of an sqaure movement enemy
				if(e[x][y] >= 'a' && e[x][y] <= 'd')
				{
					char enemyType = e[x][y];
					for(int i = x+1; i < e.size(); i++) //find the dist of square the enmemy walks
					{
						if(e[i][y] == enemyType)
						{
							std::cout << "found match for " << enemyType << " at " << x <<", " << y <<" and for i " << i <<std::endl;
							//here we found the dist of side (i-x) and know the type of enemy
							int dist = i-x;
							Cubester *creature = new Cubester(sceneMgr, pos, x, y, dist, enemyType);
							cubesters.push_back(creature);
							//remove the creature from the parser
							e[x][y] = 'x';
							e[x+dist][y] = 'x';
							e[x][y+dist] = 'x';
							e[x+dist][y+dist] = 'x';
							break;
						}
					}
				}
			}


			//increment position
			pos.x = pos.x + AbstractTile::length(); // + length to the right in 2d
		}
		pos.z = pos.z + AbstractTile::length(); // + length downward in 2d
		pos.x = centerOfTopleftTilePos.x; // reset the x 
	}
}

Map::~Map()
{
	for(int x = 0; x < getLength(); x++)
	{
		for(int y = 0; y < getLength(); y++)
		{
			std::string name = patch::to_string(x) + "y" + patch::to_string(y);
			Ogre::SceneNode* node = mgr->getSceneNode(name); 
			destroyNode(node);
			node->removeAndDestroyAllChildren();
			node->getCreator()->destroySceneNode(node);
			delete map[x][y];
		}
		map[x].clear();
	}
	map.clear();


	for(int x = 0; x < cubesters.size(); x++)
	{
		std::string name = cubesters[x]->getName();
		Ogre::SceneNode* node = mgr->getSceneNode(name); 
		destroyNode(node);
		node->removeAndDestroyAllChildren();
		node->getCreator()->destroySceneNode(node);
		delete cubesters[x];
	}
	cubesters.clear();

	std::string name = "playerNode";
	Ogre::SceneNode* node = mgr->getSceneNode(name); 
	destroyNode(node);
	node->removeAndDestroyAllChildren();
	node->getCreator()->destroySceneNode(node);
	delete player;

}

int Map::getLength()
{
	return map.size();
}

bool Map::move(int direction)
{
	int nextX = player->getPlayerX();
	int nextY = player->getPlayerY();
	if(direction == 0)      // up
	{
		nextX--;
	}
	else if(direction == 1) // right
	{
		nextY++;
	}
	else if(direction == 2) // down
	{
		nextX++;
	}
	else if(direction == 3) // left
	{
		nextY--;
	}

	if(canMove(nextX, nextY, direction))
	{
		return player->move(direction, map[nextX][nextY]->getPosition());
	}
	else
		return false;
}

bool Map::canMove(int tileX, int tileY, int direction)
{
	if(tileX < 0 || tileY < 0 || tileX >= getLength() || tileY >= getLength()) //case: out of bounds
		return false;

	if(map[tileX][tileY]->getIsWalkable(player))
	{
		return true; //exists and is walkable
	}
	else //tile is not walkabe
	{
		return false;
	}
}

void Map::simulate(const Ogre::Real elapsedTime)
{
	bool eventFire = player->simulate(elapsedTime);
	if(eventFire)
	{
		map[player->getPlayerX()][player->getPlayerY()]->event(player);
		player->updateStatus();
	}

	for(int x = 0; x < cubesters.size(); x++)
	{
		cubesters[x]->simulate(elapsedTime);
	}
	//loop through enemy/player and call thier simulate method
}

void Map::destroyNode(Ogre::SceneNode* node)
{
	if(!node) return;

	// Destroy all the attached objects
	Ogre::SceneNode::ObjectIterator itObject = node->getAttachedObjectIterator();

	while ( itObject.hasMoreElements() )
	  node->getCreator()->destroyMovableObject(itObject.getNext());

	// Recurse to child SceneNodes
	Ogre::SceneNode::ChildNodeIterator itChild = node->getChildIterator();

	while ( itChild.hasMoreElements() )
	{
	  Ogre::SceneNode* pChildNode = static_cast<Ogre::SceneNode*>(itChild.getNext());
	  destroyNode( pChildNode );
	}
}

void Map::destoryAllSceneNodes()
{
	//destory tiles
	// for (int x = 0; x < map.size(); x++)
	// {
	// 	for(int y = 0; y < map.size(); y++)
	// 	{  
	// 		std::string name = patch::to_string(x) + "y" + patch::to_string(y);
	// 		Ogre::SceneNode* node = mgr->getSceneNode("playerNode"); 
	// 		destroyNode(node);
	// 		node->removeAndDestroyAllChildren();
	// 		node->getCreator()->destroySceneNode(node);
	// 	}
	// }

	// //destroy cubesters
	// for (int x = 0; x < cubesters.size(); x++)
	// {
	// 	Ogre::SceneNode* node = cubesters[x]->rootNode; 
	// 	destroyNode(node);
	// 	node->removeAndDestroyAllChildren();
	// 	node->getCreator()->destroySceneNode(node);
	// }
}