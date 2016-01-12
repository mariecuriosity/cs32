#ifndef MAGIC_AXE
#define MAGIC_AXE

#include "Weapons.h"
#include "constants.h"

class MagicAxe : public Weapons
{
public:
	MagicAxe(Dungeon * d, Actor * a);
	virtual void abstract() {};
private:
};

#endif MAGIC_AXE