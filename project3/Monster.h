#ifndef MONSTER_INCLUDED
#define MONSTER_INCLUDED

#include "utilities.h"
#include "Actor.h"
#include "GameObjects.h"

class Monster :public Actor
{
public:
	Monster(Dungeon *d, int hitPoints, int armorPoints, int strengthPoints,
		int dexterityPoints, string startingWeapon, int smellDistance, double hpProb, double dropProb);
	virtual ~Monster();
	virtual string move();
	char playerNearBy(); //returns direction to move. if too far, returns "f"
	bool isNextTo();
	virtual char actorType() = 0;
	virtual string attack();
	void dropItem(double prob);
	virtual bool isAlive();
private:
	int m_smellDistance;
	double m_hpProb;
	double m_dropProb;
	GameObjects * m_object;
};


#endif MONSTER_INCLUDED