#ifndef DRAGONS_INCLUDED
#define DRAGONS_INCLUDED

#include "utilities.h"
#include "Dungeon.h"
#include "Actor.h"
#include "Monster.h"

class Dragons :public Monster
{
public:
	Dragons(Dungeon * d);
	virtual ~Dragons();
	virtual char actorType();
	virtual string move();
private:
};

#endif DRAGONS_INCLUDED