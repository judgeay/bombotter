#include "MapModel.h"
#include "PlayerModel.h"
#include "MapItem.h"
#include "BombItem.h"
#include "VoidItem.h"
#include "BoxItem.h"
#include "RockItem.h"
#include "ExplosionItem.h"
#include "FlameUp.h"
#include "BombUp.h"
#include "SpeedUp.h"
#include "Kicker.h"
#include "Bomberloutre.h"
#include <time.h>
#include <iostream>
#include <fstream>

MapModel::MapModel(int _height, int _width)
{
	this->height = _height;
	this->width = _width;
}

MapModel::~MapModel()
{
	//CODE TON PUTAIN DE BOT !
}

void MapModel::addPlayer(PlayerModel* newPlayer)
{
	bool find = false;
	for(std::vector<PlayerModel*>::iterator i=listPlayer.begin();i!=listPlayer.end();++i)
	{
		if((*i) == newPlayer)
		{
			find = true;
		}
	}
	if(!find)
	{
		this->listPlayer.push_back(newPlayer);
	}
}

void MapModel::checkMove(PlayerModel* p, ::BomberLoutreInterface::Point arrive)
{

	int posXPlayer, posYPlayer, minX, maxX, minY, maxY, bordX1, bordY1, bordX0, bordY0;
	bool valid = true;

	posXPlayer = arrive.x;
	posYPlayer = arrive.y;

	minX = posXPlayer + 7;
	maxX = posXPlayer + 57;
	minY = posYPlayer + 11;
	maxY = posYPlayer + 61;
	
	switch(p->getDir())
	{
		case PlayerModel::dirLeft:
			bordX0 = minX/60;
			bordY0 = minY/60;
			bordX1 = minX/60;
			bordY1 = maxY/60;
			break;
		case PlayerModel::dirRight:
			bordX0 = maxX/60;
			bordY0 = minY/60;
			bordX1 = maxX/60;
			bordY1 = maxY/60;
			break;
		case PlayerModel::dirUp:
			bordX0 = minX/60;
			bordY0 = minY/60;
			bordX1 = maxX/60;
			bordY1 = minY/60;
			break;
		case PlayerModel::dirDown:
			bordX0 = minX/60;
			bordY0 = maxY/60;
			bordX1 = maxX/60;
			bordY1 = maxY/60;
			break;
	}
	if(this->testCase(bordX0, bordY0, p))
	{
		valid = this->testCase(bordX1, bordY1, p);
	} else {
		valid = false;
	}

	if(valid)
	{
		p->setPosX(arrive.x);
		p->setPosY(arrive.y);
	}
}

bool MapModel::testCase(int bordX, int bordY, PlayerModel* p)
{
	switch(this->logicalMap[bordY][bordX])
	{
	case BoxItemCode:		
	case RockItemCode:
		return false;
		break;
	case BombItemCode:
		return false;//rajouter le kikable
		break;
	case ExplosionItemCode:
		p->die(((ExplosionItem*)(this->map[bordY][bordX]))->getPlayer());
		((ExplosionItem*)(this->map[bordY][bordX]))->getPlayer()->addKill(1);
		break;
	case FlameUpCode:
	case GoldenFlameCode:
	case BombUpCode:
	case SpeedUpCode:
	case KickerCode:
	case InvisibleItemCode:
	case InvincibleItemCode:
	case ShieldItemCode:
		p->addBonus((Bonus*)this->map[bordY][bordX]);
		break;
	}
	return true;
}

void MapModel::createMapItem(int typeMapItem, ::BomberLoutreInterface::Point p, PlayerModel *player)
{
	switch(typeMapItem)
	{
	case VoidItemCode:
		this->map[p.y][p.x] = new VoidItem(this);
		this->logicalMap[p.y][p.x] = VoidItemCode;
		break;
	case BoxItemCode:
		this->map[p.y][p.x] = new BoxItem(this);
		this->logicalMap[p.y][p.x] = BoxItemCode;
		break;
	case RockItemCode:
		this->map[p.y][p.x] = new RockItem(this);
		this->logicalMap[p.y][p.x] = RockItemCode;
		break;
	case BombItemCode:
		this->map[p.y][p.x] = new BombItem(this, player, player->getPower());
		this->logicalMap[p.y][p.x] = BombItemCode;
		break;
	case ExplosionItemCode:
		this->map[p.y][p.x] = new ExplosionItem(this, player);
		this->logicalMap[p.y][p.x] = ExplosionItemCode;
		break;

	case FlameUpCode:
		this->map[p.y][p.x] = new FlameUp(this);
		this->logicalMap[p.y][p.x] = FlameUpCode;
		break;
	case GoldenFlameCode:
		break;
	case BombUpCode:
		this->map[p.y][p.x] = new BombUp(this);
		this->logicalMap[p.y][p.x] = BombUpCode;
		break;
	case SpeedUpCode:
		this->map[p.y][p.x] = new SpeedUp(this);
		this->logicalMap[p.y][p.x] = SpeedUpCode;
		break;
	case KickerCode:
		this->map[p.y][p.x] = new Kicker(this);
		this->logicalMap[p.y][p.x] = KickerCode;
		break;
	case InvisibleItemCode:
		break;
	case InvincibleItemCode:
		break;
	case ShieldItemCode:
		break;
	}
}

void MapModel::dropBonus(BoxItem* box)
{
	bool find = false;
	::BomberLoutreInterface::Point position;

	position.x = 0;
	position.y =0;

	for(int i = 0; i < MAPHEIGHT; i++)
	{
		for(int j = 0; i < MAPWIDTH; i++)
		{
			if(this->map[j][i] == box)
			{
				position.x = i;
				position.y= j;
				find = true;
			}
		}
	}
	if(find)
	{
		float randomDrop;
		srand(time(NULL));
		randomDrop = rand() / float(RAND_MAX);

		if( randomDrop <= box->getDropChances())
		{
			this->dropBonus(position);
		}
	}
}

void MapModel::dropBonus(VoidItem* voidItem)
{
	bool find = false;
	::BomberLoutreInterface::Point position;
	position.x = 0;
	position.y =0;

	for(int i = 0; i < MAPHEIGHT; i++)
	{
		for(int j = 0; i < MAPWIDTH; i++)
		{
			if(this->map[j][i] == voidItem)
			{				
				position.x = i;
				position.y = j;
				find = true;
			}
		}
	}
	if(find)
	{
		float randomDrop;
		int randomItem, itemCode;
		srand(time(NULL));
		randomDrop = rand() / float(RAND_MAX);

		if( randomDrop <= voidItem->getDropChances())
		{
			this->dropBonus(position);
		}
	}
}

void MapModel::dropBonus(::BomberLoutreInterface::Point p)
{
	int randomItem, itemCode;
	randomItem = (rand() / float(RAND_MAX)) * 4 +1;
	switch(randomItem)
	{
		case 1:
			itemCode = MapModel::FlameUpCode;
			break;
		case 2:
			itemCode = MapModel::BombUpCode;
			break;
		case 3:
			itemCode = MapModel::SpeedUpCode;
			break;
		case 4:
			itemCode = MapModel::KickerCode;
			break;
	}
	this->createMapItem(itemCode, p, NULL);
}

void MapModel::handleExplode(BombItem* b)
{
	bool find = false;
	int posXPlayer;
	int posYPlayer;
	int maxX, minX, maxY, minY;
	int range = b->getPower();
	::BomberLoutreInterface::Point position;
	
	position.x = 0;
	position.y = 0;

	for(int i = 0; i < MAPHEIGHT; i++)
	{
		for(int j = 0; i < MAPWIDTH; i++)
		{
			if(this->logicalMap[j][i] == BombItemCode)
			{
				position.x = i;
				position.y = j;
				find = true;
			}
		}
	}

	if(find)
	{
		for (int dir=PlayerModel::dirLeft; dir<= PlayerModel::dirDown; dir++)
		{
			bool goOut = false;
			int distance = 1;
			::BomberLoutreInterface::Point pp;

			while (distance<=range && !goOut)
			{
				int x0=position.x, y0=position.y;
				switch (dir)
				{
					case PlayerModel::dirLeft: x0-=distance; break;
					case PlayerModel::dirRight: x0+=distance; break;
					case PlayerModel::dirUp: y0+=distance; break;
					case PlayerModel::dirDown: y0-=distance; break;
				}

				switch (this->logicalMap[y0][x0])
				{
					case VoidItemCode:
						pp.x = x0;
						pp.y = y0;
						this->createMapItem(ExplosionItemCode, pp, b->getPlayer()); 
						break;
					case RockItemCode: goOut=true; break;
					case ExplosionItemCode: 
						pp.x = x0;
						pp.y = y0;
						this->createMapItem(ExplosionItemCode, pp, b->getPlayer());
						break;
					case BoxItemCode: ((BoxItem*)(this->map[y0][x0]))->disappears(); goOut=true; break;
					case FlameUpCode: 
					case GoldenFlameCode: 
					case BombUpCode:  
					case SpeedUpCode:  
					case KickerCode: 
					case InvisibleItemCode:  
					case InvincibleItemCode: 
					case ShieldItemCode:   
						pp.x = x0;
						pp.y = y0;
						this->createMapItem(ExplosionItemCode, pp, b->getPlayer());
						break;
					case BombItemCode: this->handleExplode((BombItem*)this->map[y0][x0]); break;
				}
				minX = x0 * this->height;
				maxX = x0 * this->height + this->height;
				minY = y0 * this->width;
				maxY = y0 * this->width + this->width;

				for(std::vector<PlayerModel*>::iterator i=listPlayer.begin();i!=listPlayer.end();++i)
				{
					if((*i)->isAlive()){

						posXPlayer = (*i)->getPosX();
						posYPlayer = (*i)->getPosY();
						if(posYPlayer + 61 > minY
							&& posYPlayer + 7 < maxY
							&& posXPlayer + 57 > minX
							&& posXPlayer + 11 < maxX)
						{
							(*i)->die(b->getPlayer());
							b->getPlayer()->addKill(1);
						}
					}
				}
				distance++;
			}
		}
	}
}

void MapModel::dropBomb(PlayerModel *p)
{
	int posXPlayer, posYPlayer;

	posXPlayer = p->getPosX() + 32;
	posYPlayer = p->getPosY() + 36;

	switch(this->logicalMap[posXPlayer][posYPlayer])
	{
	case BoxItemCode:		
	case RockItemCode:
		break;
	case BombItemCode:
	case VoidItemCode:
	case ExplosionItemCode:
	case FlameUpCode:
	case GoldenFlameCode:
	case BombUpCode:
	case SpeedUpCode:
	case KickerCode:
	case InvisibleItemCode:
	case InvincibleItemCode:
	case ShieldItemCode:
		::BomberLoutreInterface::Point point;
		point.x = posXPlayer;
		point.y = posYPlayer;
		this->createMapItem(BombItemCode, point, p);
		p->incNbBombUsed();
		break;
	}

}

void MapModel::loapMap(string id)
{
	FILE * pFile;
	  	pFile = fopen (id,"rw");
  	char currentChar;
  	int ligne = 0, colonne = 0;
  	if (pFile!=NULL)
  	{
    	do
    	{
      		currentChar = fgetc(pFile);
      	    switch(currentChar)
      	    {
      	    	case ';':
      	    	{
      	    		++colonne;
      	    	}break;
      	    	case '\n':
      	    	{
      	    		++ligne;
      	    		colonne=0;
      	    	}break;
      	    	case '\r':
      	    	break;
      	    	case ' ':
      	    	break;
      	    	case '#':
      	    	break;
      	    	default:
      	    	{
					::BomberLoutreInterface::Point position;
					position.x = ligne;
					position.y = colonne;
      	    		createMapItem(currentChar, position, NULL);
      	    	}break;
      	    }
    	}while (currentChar != EOF && currentChar != '#');	
    	
    	fclose (pFile);
  	}
  	else
  		cout << "Unable to open file"; 
}

::std::string MapModel::getId(const ::Ice::Current&)
{
	return this->id;
}

::Ice::Int MapModel::getWidth(const ::Ice::Current&)
{
	return width;
}

::Ice::Int MapModel::getHeight(const ::Ice::Current&)
{
	return height;
}
 
void MapModel::moveUp(const ::BomberLoutreInterface::Player& p, const ::Ice::Current&)
{
	for(std::vector<PlayerModel*>::iterator i=listPlayer.begin();i!=listPlayer.end();++i)
	{
		if((*i)->getGameTag() == p.related.gameTag )
		{
			(*i)->moveUp();
		}
	}
}

void MapModel::moveDown(const ::BomberLoutreInterface::Player& p, const ::Ice::Current&)
{
	for(std::vector<PlayerModel*>::iterator i=listPlayer.begin();i!=listPlayer.end();++i)
	{
		if((*i)->getGameTag() == p.related.gameTag )
		{
			(*i)->moveDown();
		}
	}
}
 
void MapModel::moveLeft(const ::BomberLoutreInterface::Player& p, const ::Ice::Current&)
{
	for(std::vector<PlayerModel*>::iterator i=listPlayer.begin();i!=listPlayer.end();++i)
	{
		if((*i)->getGameTag() == p.related.gameTag )
		{
			(*i)->moveLeft();
		}
	}
}

void MapModel::moveRight(const ::BomberLoutreInterface::Player& p, const ::Ice::Current&)
{
	for(std::vector<PlayerModel*>::iterator i=listPlayer.begin();i!=listPlayer.end();++i)
	{
		if((*i)->getGameTag() == p.related.gameTag )
		{
			(*i)->moveRight();
		}
	}
}
 
void MapModel::dropBomb(const ::BomberLoutreInterface::Player& p, const ::BomberLoutreInterface::Bomb& b, const ::Ice::Current&)
{
	for(std::vector<PlayerModel*>::iterator i=listPlayer.begin();i!=listPlayer.end();++i)
	{
		if((*i)->getGameTag() == p.related.gameTag )
		{
			(*i)->dropBomb();
		}
	}
}
