#include "ScrollOfRaiseStrength.h"
#include "Player.h"

SoRaiseStrength::SoRaiseStrength(Dungeon * d, Actor * a)
	: Scrolls(d, a, "scroll of raise strength")
{

}

string SoRaiseStrength::read()
{
	if (!canRead())
		return string();
	dungeon()->player()->addStengthPoints(1 + randInt(3));
	setAsRead();
	return "You read the scroll called scroll of raise strength\nYou feel like less of a klutz.\n";

}