#ifndef SOEH_INCLUDED
#define SOEH_INCLUDED

#include "constants.h"
#include "Scrolls.h"

class SoEnhanceHealth : public Scrolls
{
public:
	SoEnhanceHealth(Dungeon * d, Actor * a);
	virtual string read();
private:
};



#endif SOEH_INCLUDED