#include "Snakewomen.h"

//Monster(Dungeon *d, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, string startingWeapon, int smellDistance);
Snakewomen::Snakewomen(Dungeon * d) :Monster(d, 3 + randInt(4), 3, 2, 3, W_MF, 3,SNAKEWOMEN_HP_REGAIN_PROB,1/3)
{

}

Snakewomen::~Snakewomen()
{

}

char Snakewomen::actorType()
{
	return M_S;
}