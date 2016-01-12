#include "ScrollOfEnhanceHealth.h"
#include "Player.h"

SoEnhanceHealth::SoEnhanceHealth(Dungeon * d, Actor * a)
	: Scrolls(d, a, S_EH)
{

}

string SoEnhanceHealth::read()
{
	if (!canRead())
		return string();
	dungeon()->player()->increaseMaxHitPoints(3 + randInt(6));
	setAsRead();
	return "You read the scroll called scroll of enhance health\nYou feel like less of a klutz.\n";

}