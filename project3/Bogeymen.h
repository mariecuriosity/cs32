#ifndef BOGEYMEN_INCLUDED
#define BOGEYMEN_INCLUDED

#include "utilities.h"
#include "Dungeon.h"
#include "Actor.h"
#include "Monster.h"

class Bogeymen:public Monster
{
public:
	Bogeymen(Dungeon * d);
	~Bogeymen();
	virtual char actorType();
private:
};

#endif BOGEYMEN_INCLUDED