#ifndef WEAPONS_INCLUDED
#define WEAPONS_INCLUDED

#include "GameObjects.h"
#include "constants.h"

class Weapons: public GameObjects
{
public:
	Weapons(Dungeon * d, Actor * a, string weaponType);
	virtual ~Weapons();
	virtual string actionString(Actor* m) const;
	string attackResult(Actor * defender) const;
	int getWeaponDamageAmount() const;
	string actorCharToString(char actor) const;
	virtual void abstract() = 0;
private:
	string getWeaponAction() const;
	int getWeaponDexterityBonus() const;
};


#endif WEAPONS_INCLUDED