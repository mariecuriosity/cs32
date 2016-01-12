#ifndef MAGICFANG_INCLUDED
#define MAGICFANG_INCLUDED

#include "Weapons.h"
#include "constants.h"
#include "Actor.h"

class MagicFang : public Weapons
{
public:
	MagicFang(Dungeon * d, Actor * a);
	virtual string actionString(Actor* m) const;
	virtual void abstract() {};
private:
};


#endif MAGICFANG_INCLUDED