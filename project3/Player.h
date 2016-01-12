#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "Actor.h"
#include "constants.h"
#include "GameObjects.h"
#include "Monster.h"
#include "Weapons.h"
#include "Scrolls.h"
#include "Idol.h"
#include <vector>
#include <conio.h>

class Player :public Actor
{
public:
	Player(Dungeon *d);
	virtual ~Player();
	string move(char dir); //returns true if valid move (no walls)
	virtual char actorType();
	virtual string attack(char dir);
	void printInventory();
	bool addObject(GameObjects * object);
	void increaseMaxHitPoints(int amountToIncrease);
	void increaseArmor(int amountToIncrease);
	virtual void addHitPoints(double prob);
	bool copyItems(Dungeon * d);
private:
	GameObjects * m_inventory[PLAYER_MAX_INVENTORY];
	GameObjects * m_currItem;
	bool addItem(string itemType); //returns true if there is room
	int m_nItems;
	int m_maxHitPoints = 20;
};

#endif PLAYER_INCLUDED
