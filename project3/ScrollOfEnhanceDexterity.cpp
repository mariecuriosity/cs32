#include "ScrollOfEnhanceDexterity.h"
#include "Player.h"

SoEnhanceDexterity::SoEnhanceDexterity(Dungeon * d, Actor * a)
	: Scrolls(d, a, S_ED)
{

}

string SoEnhanceDexterity::read()
{
	if (!canRead())
		return string();
	dungeon()->player()->raiseDexterity();
	setAsRead();
	return "You read the scroll called scroll of enhance dexterity\nYou feel like less of a klutz.\n";

}