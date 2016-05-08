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

Map::Map(Player *play, Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos,
		 std::vector< std::string > v, std::vector< std::string > e):
mgr(sceneMgr), player(play)
{
	parseMaps(centerOfTopleftTilePos, v, e);
	name = "chris";
}

Map::Map(Player *play, Ogre::SceneManager* sceneMgr, Ogre::Vector3 centerOfTopleftTilePos, int catNum, int levNum):
mgr(sceneMgr), player(play)
{
	Level l(catNum, levNum);
	name = l.getName();
	parseMaps(centerOfTopleftTilePos, l.getTileMap(), l.getCubesterMap());
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
		Ogre::Vector3 addPlayerLength = map[nextX][nextY]->getPosition();
		addPlayerLength.y += Player::length()/2;
		return player->move(direction, addPlayerLength);
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

std::string Map::getName()
{
	return name;
}

bool checkCollision(Ogre::Vector3 p, Ogre::Vector3 c)
{
	double distX = abs(p.x - c.x);
	double distY = abs(p.z - c.z);
	return (distX < 46 && distY < 46); //50 is a bit harsh on the collision
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
		cubesters[x]->simulate(elapsedTime, player->rootNode->getPosition());
		if(checkCollision(player->rootNode->getPosition(), cubesters[x]->getPosition()))
			player->kill();
	}

	if(!player->isAlive())
	{
		player->respawn();
		for(int x = 0; x < map.size(); x++)
		{
			for(int y = 0; y < map.size(); y++)
			{
				map[x][y]->reload();
			}
		}
		for(int x = 0; x < cubesters.size(); x++)
		{
			cubesters[x]->reload();
		}
	}
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

//Modes for the map
// 0 == default
// 1 == rakan 40% of the tiles (random)
// 2 == lol
// 3 == skyrim
// 4 == mario
// 5 == zelda
// 6 == (secret)
// 7 == mine fire
// 8 == mine water
// 9 == mine dirt
// !@#$%^&*() unused could be 10-19
void Map::parseMaps(Ogre::Vector3 centerOfTopleftTilePos,
		 	   std::vector< std::string > v, std::vector< std::string > e)
{
	Tile *temp;
	Ogre::Vector3 pos(centerOfTopleftTilePos.x, centerOfTopleftTilePos.y, centerOfTopleftTilePos.z);
	int mode = 0;
	for(int x = 0; x < v.size(); x++)
	{
		map.push_back(std::vector<Tile *>());
		for(int y = 0; y < v.size(); y++)
		{
			// code for the tiles
			if(isdigit(v[x][y]) /* || symbol stuff here and change the -48 */)
			{
				mode = ((int)v[x][y]) - '0'; //put character down to int
				v[x][y] = 'x';
				temp = new Tile(mgr,pos, x, y, v[x][y], mode);
			}
			else
			{
				temp = new Tile(mgr,pos, x, y, v[x][y], mode);
			}
			map[x].push_back(temp);
			if(v[x][y] == Tile::typeForStartTile())
			{
				player->setPlayerCord(x,y, AbstractTile::length(), centerOfTopleftTilePos.z, centerOfTopleftTilePos.x);
			}
			//code for enemy locations
			if(e[x][y] != 'x' && e[x][y] != '+' && e[x][y] != '*')
			{
				char enemyType = e[x][y];
				char lowerCaseEnemyType = tolower(enemyType);
				//know it should be part of a clockwise square movement enemy
				if(lowerCaseEnemyType >= 'a' && lowerCaseEnemyType <= 'd')
				{
					for(int j = y+1; j < e.size(); j++) //find the dist of square the enmemy walks
					{
						if(e[x][j] == enemyType)
						{
							//here we found the dist of side (i-x) and know the type of enemy
							int dist = j-y;
							Cubester *creature = new Cubester(mgr, pos, x, y, dist, lowerCaseEnemyType);
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
				// know it should be part of a counter clockwise square movement enemy
				else if(lowerCaseEnemyType >= 'm' && lowerCaseEnemyType <= 'p')
				{
					for(int j = y+1; j < e.size(); j++) //find the dist of square the enmemy walks
					{
						if(e[x][j] == enemyType)
						{
							//here we found the dist of side (i-x) and know the type of enemy
							int dist = j-y;
							Cubester *creature = new Cubester(mgr, pos, x, y, dist, lowerCaseEnemyType);
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

				//know it should be part of a horizontal enemy
				else if(lowerCaseEnemyType == 'l' || lowerCaseEnemyType == 'r' || lowerCaseEnemyType == 'i' || lowerCaseEnemyType == 'k')
				{
					for(int j = y+1; j < e.size(); j++) //find the dist of square the enmemy walks
					{
						if(e[x][j] == enemyType)
						{
							//here we found the dist of side (i-x) and know the type of enemy
							int dist = j-y;
							Cubester *creature = new Cubester(mgr, pos, x, y, dist, lowerCaseEnemyType);
							cubesters.push_back(creature);
							//remove the creature from the parser
							e[x][y] = 'x';
							e[x][y+dist] = 'x';
							break;
						}
					}
				}

				//know it should be part of a vertical enemy
				else if(lowerCaseEnemyType == 'y' || lowerCaseEnemyType == 'u' || lowerCaseEnemyType == 'h' || lowerCaseEnemyType == 'j')
				{
					for(int i = x+1; i < e.size(); i++) //find the dist of square the enmemy walks
					{
						if(e[i][y] == enemyType)
						{
							//here we found the dist of side (i-x) and know the type of enemy
							int dist = i-x;
							Cubester *creature = new Cubester(mgr, pos, x, y, dist, lowerCaseEnemyType);
							cubesters.push_back(creature);
							//remove the creature from the parser
							e[x][y] = 'x';
							e[x+dist][y] = 'x';
							break;
						}
					}
				}

				else if(lowerCaseEnemyType >= '0' &&  lowerCaseEnemyType <= '9' )
				{
					
					int dist = (int)(lowerCaseEnemyType - 48);
					Cubester *creature = new Cubester(mgr, pos, x, y, dist, 'z');
					cubesters.push_back(creature);
					//remove the creature from the parser
					e[x][y] = 'x';
				}
			}
			//increment position
			pos.x += AbstractTile::length(); // + length to the right in 2d
		}
		pos.z += AbstractTile::length(); // + length downward in 2d
		pos.x = centerOfTopleftTilePos.x; // reset the x 
	}

	for(int x = 0; x < map.size(); x++)
	{
		for(int y = 0; y < map.size(); y++)
		{
			if(v[x][y] == Tile::typeForIceTile())
			{
				Tile *up = NULL;
				Tile *right = NULL;
				Tile *down = NULL;
				Tile *left = NULL;
				//check above tile
				if(x-1 >= 0)
					up = map[x-1][y];
				//check right tile
				if(y+1 < map.size())
					right = map[x][y+1];
				//check down tile
				if(x+1 < map.size())
					down = map[x+1][y];
				//check left tile
				if(y-1 >= 0)
					left = map[x][y-1];
				map[x][y]->setNeighbors(up,right,down,left);
			}
		}
	}
}