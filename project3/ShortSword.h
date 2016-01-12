#ifndef SHORTSWORD_INCLUDED
#define SHORTSWORD_INCLUDED

#include "Weapons.h"
#include "constants.h"

class ShortSword : public Weapons
{
public:
	ShortSword(Dungeon * d, Actor * a);
	virtual void abstract() {};
private:
};


#endif SHORTSWORD_INCLUDED