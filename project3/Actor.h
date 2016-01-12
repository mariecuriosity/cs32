#ifndef ACTOR_INCLUDED
#define ACTOR_INCLUDED

using namespace std;
#include <string>
#include "Dungeon.h"
#include "GameObjects.h"
#include "constants.h"

class Actor
{
public:
	Actor(Dungeon *d, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, string startingWeapon);
	void initializeSpot();
	virtual ~Actor(){}
	int getRow() const;
	int getCol() const;
	bool setOneAway(char dir); //returns true if valid and within one space from original
	void addArmorPoints(int amountToIncrease);
	void addHitPoints();
	void addStengthPoints(int amountToIncrease);
	void raiseDexterity();
	int getHitPoints() const;
	int getArmorPoints() const;
	int getStengthPoints() const;
	int getDexterityPoints() const;
	int getSleepTime() const;
	bool decreaseHitPoints(int numberToDecrease); // returns true if actor is still alive
	virtual bool isAlive() const;
	void setSleepTime(int sleepTime);
	Dungeon* dungeon() const;
	virtual char actorType() = 0;
	virtual void addHitPoints(double prob);
	void switchDungeon(Dungeon * d);
	void cheat();
private:
	Dungeon * m_dungeon;
	int m_row;
	int m_col;
	int m_hitPoints;
	int m_maxHitPoints;
	int m_armorPoints;
	int m_stengthPoints;
	int m_dexterityPoints;
	int m_sleepTime;
	char m_actorType;
};


#endif ACTOR_INCLUDED