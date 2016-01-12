#ifndef SORS_INCLUDED
#define SORS_INCLUDED

#include "Scrolls.h"

class SoRaiseStrength:public Scrolls
{
public:
	SoRaiseStrength(Dungeon * d, Actor * a);
	virtual string read();
private:
};


#endif SORS_INCLUDED