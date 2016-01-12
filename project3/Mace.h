#ifndef MACE_INCLUDED
#define MACE_INCLUDED

#include "Weapons.h"
#include "constants.h"

class Mace : public Weapons
{
public:
	Mace(Dungeon * d, Actor * a);
	virtual void abstract() {};
private:
};


#endif MACE_INCLUDED