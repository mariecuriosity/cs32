#ifndef SOIA_INCLUDED
#define SOIA_INCLUDED

#include "Scrolls.h"

class SoImproveArmor: public Scrolls
{
public:
	SoImproveArmor(Dungeon * d, Actor * a);
	virtual string read();
private:

};

#endif SOIA_INCLUDED