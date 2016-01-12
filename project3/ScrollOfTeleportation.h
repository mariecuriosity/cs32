#ifndef SOT_INCLUDED
#define SOT_INCLUDED

#include "constants.h"
#include "Scrolls.h"

class SoTeleportation : public Scrolls
{
public:
	SoTeleportation(Dungeon * d, Actor * a);
	virtual string read();
private:
};



#endif SOT_INCLUDED