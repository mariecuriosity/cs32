#include "ScrollOfImproveArmor.h"
#include "Player.h"

SoImproveArmor::SoImproveArmor(Dungeon * d, Actor * a)
	: Scrolls(d, a, "scroll of improve armor")
{

}

string SoImproveArmor::read()
{
	if (!canRead())
		return string();
	dungeon()->player()->addArmorPoints(1 + randInt(3));
	setAsRead();
	return "You read the scroll called scroll of improve armor\nYou feel like less of a klutz.\n";

}