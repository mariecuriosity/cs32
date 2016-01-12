#include "ScrollOfTeleportation.h"
#include "Player.h"

SoTeleportation::SoTeleportation(Dungeon * d, Actor * a)
	: Scrolls(d, a, "scroll of teleporatation")
{

}

string SoTeleportation::read()
{
	if (!canRead())
		return string();
	dungeon()->player()->initializeSpot();
	setAsRead();
	return "You read the scroll called scroll of enhance dexterity\nYou feel like less of a klutz.\n";
}