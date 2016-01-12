#include "Weapons.h"
#include "Actor.h"


Weapons::Weapons(Dungeon * d, Actor * a, string weaponType)
	:GameObjects(d, a, weaponType)
{
}

Weapons::~Weapons()
{

}

string Weapons::getWeaponAction() const
{
	if (getObjectType() == W_SS)
		return W_SSAc;
	else if (getObjectType() == W_LS)
		return W_LSAc;
	else if (getObjectType() == W_M)
		return W_MAc;
	else if (getObjectType() == W_MA)
		return W_MAAc;
	else if (getObjectType() == W_MF)
		return W_MFAc;
	else
		return DEFAULT_STRING;
}

int Weapons::getWeaponDamageAmount() const
{
	if (getObjectType() == W_SS)
		return W_SS_D;
	else if (getObjectType() == W_LS)
		return W_LS_D;
	else if (getObjectType() == W_M)
		return W_M_D;
	else if (getObjectType() == W_MA)
		return W_MA_D;
	else if (getObjectType() == W_MF)
		return W_MF_D;
	else
		return 0;
}

int Weapons::getWeaponDexterityBonus() const
{
	if (getObjectType() == W_SS)
		return W_SS_DB;
	else if (getObjectType() == W_LS)
		return W_LS_DB;
	else if (getObjectType() == W_M)
		return W_M_DB;
	else if (getObjectType() == W_MA)
		return W_MA_DB;
	else if (getObjectType() == W_MF)
		return W_MF_DB;
	else
		return 0;
}


string Weapons::attackResult(Actor * defender) const
{
	int attackerPoints = getActor()->getDexterityPoints() + getWeaponDexterityBonus();
	int defenderPoints = defender->getDexterityPoints() + defender->getArmorPoints();
	if (randInt(attackerPoints) >= randInt(defenderPoints))
	{
		defender->decreaseHitPoints(randInt(getActor()->getStengthPoints() + getWeaponDamageAmount()));
		return HIT;
	}
	else
		return MISS;
}

string Weapons::actorCharToString(char actorType) const
{
	switch (actorType)
	{
	default:
		return DEFAULT_STRING;
	case M_S:
		return "the Snakewoman";
	case M_G:
		return "the Goblin";
	case M_B:
		return "the Bogeyman";
	case M_D:
		return "the Dragon";
	case M_P:
		return "Player";
	}
}

string Weapons::actionString(Actor * p) const
{
	if (!isPickedUp() || p == nullptr)
		return string();
	string attacker = actorCharToString(getActor()->actorType());
	string victim = actorCharToString(p->actorType());	
	string attack = attackResult(p);
	if (!p->isAlive())
		return attacker + " " + getWeaponAction() + " " + getObjectType() + " at " + victim + " dealing a final blow.\n";
	return attacker + " " + getWeaponAction() + " " + getObjectType() + " at " + victim + " and " + attack + ".\n";
}