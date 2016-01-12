#ifndef LONGSWORD_INCLUDED
#define LONGSWORD_INCLUDED

#include "Weapons.h"
#include "constants.h"

class LongSword : public Weapons
{
public:
	virtual void abstract() {};
	LongSword(Dungeon * d, Actor * a);
private:
};


#endif LONGSWORD_INCLUDED