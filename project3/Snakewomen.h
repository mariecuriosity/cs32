#ifndef SNAKEWOMEN_INCLUDED
#define SNAKEWOMEN_INCLUDED

#include "utilities.h"
#include "Dungeon.h"
#include "Actor.h"
#include "Monster.h"

class Snakewomen :public Monster
{
public:
	Snakewomen(Dungeon * d);
	~Snakewomen();
	virtual char actorType();
private:
};

#endif SNAKEWOMEN_INCLUDED