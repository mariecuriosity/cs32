#include "Bogeymen.h"

Bogeymen::Bogeymen(Dungeon * d) :Monster(d, 5 + randInt(6), 2, 2 + randInt(2), 2 + randInt(2), W_SS, 5, BOGEYMEN_HP_REGAIN_PROB,.1)
{

}

Bogeymen::~Bogeymen()
{

}

char Bogeymen::actorType()
{
	return M_B;
}
