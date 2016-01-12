#ifndef SOED_INCLUDED
#define SOED_INCLUDED

#include "constants.h"
#include "Scrolls.h"

class SoEnhanceDexterity : public Scrolls
{
public:
	SoEnhanceDexterity(Dungeon * d, Actor * a);
	virtual string read();
private:
};



#endif SOED_INCLUDED