#include "Dragons.h"

Dragons::Dragons(Dungeon * d) :Monster(d, 20 + randInt(6), 4, 4, 4, W_LS, 0, DRAGONS_HP_REGAIN_PROB,1)
{

}

Dragons::~Dragons()
{

}

char Dragons::actorType()
{
	return M_D;
}

string Dragons::move()
{
	addHitPoints(DRAGONS_HP_REGAIN_PROB);
	if (isNextTo())
		return attack();
	else
	{
		return string();
	}
}