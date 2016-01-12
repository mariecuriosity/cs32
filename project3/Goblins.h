#ifndef GOBLINS_INCLUDED
#define GOBLINS_INCLUDED

#include "utilities.h"
#include "Dungeon.h"
#include "Actor.h"
#include "Monster.h"
#include "Player.h"
#include <queue>

class Goblins :public Monster
{
public:
	Goblins(Dungeon * d, int smellDistance);
	~Goblins();
	virtual char actorType();
//	virtual string move();
private:
//	Coord smellPath(char maze[][LEVEL_COLS]);
//	Coord smellPath(Coord current, Coord*maze[][LEVEL_COLS]) const;
	int m_smellDistance;
};

#endif GOBLINS_INCLUDED