#include "Actor.h"

Actor::Actor(Dungeon * d, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, string startingWeapon)
{
	if (d==nullptr)
	{
		cout << "***** An actor must be in some Dungeon!" << endl;
		exit(1);
	}
	m_dungeon = d;
	m_hitPoints = hitPoints;
	m_maxHitPoints = hitPoints;
	m_armorPoints = armorPoints;
	m_stengthPoints = strengthPoints;
	m_dexterityPoints = dexterityPoints;
	m_sleepTime = 0;
	initializeSpot();
}

Dungeon * Actor::dungeon() const
{
	return m_dungeon;
}

void Actor::switchDungeon(Dungeon * d)
{
	m_dungeon = d;
}

void Actor::addStengthPoints(int amount)
{
	m_stengthPoints += amount;
}

void Actor::raiseDexterity()
{
	++m_dexterityPoints;
}

void Actor::addHitPoints(double prob)
{
	if (prob <= 0 || m_maxHitPoints >= getHitPoints())
		return;
	if (trueWithProbability(prob))
		Actor::addHitPoints();
}


void Actor::initializeSpot()
{
	int r = 1 + randInt(LEVEL_ROWS - 1);
	int c = 1 + randInt(LEVEL_COLS - 1);
	if (m_dungeon->isOpen(r, c) && (m_dungeon->isOpen(r, c - 1) || m_dungeon->isOpen(r, c + 1))
		&& (m_dungeon->isOpen(r - 1, c) || m_dungeon->isOpen(r + 1, c)))
	{
		m_row = r;
		m_col = c;
	}
	else
		initializeSpot();
	return;
}

void Actor::addHitPoints()
{
	++m_hitPoints;
}

int Actor::getRow() const
{
	return m_row;
}

void Actor::cheat()
{
	if (actorType() != M_P)
		return;
	else
		m_hitPoints = 50;
}

int Actor::getCol() const
{
	return m_col;
}

bool Actor::setOneAway(char dir)
{
	if (dir == 'f')
		return false;
	int row = m_row;
	int col = m_col;
	switch (dir)
	{
	case ARROW_UP:     --row;				break;
	case ARROW_DOWN:   ++row;				break;
	case ARROW_LEFT:   --col;				break;
	case ARROW_RIGHT:  ++col;				break;
	}
	if (m_dungeon->isOpen(row, col))
	{
		m_row = row;
		m_col = col;
		return true;
	}
	return false;
}

int Actor::getHitPoints() const
{
	return m_hitPoints;
}

void Actor::addArmorPoints(int amount)
{
	m_armorPoints += amount;
}

int Actor::getArmorPoints() const
{
	return m_armorPoints;
}

int Actor::getStengthPoints() const
{
	return m_stengthPoints;
}

int Actor::getDexterityPoints() const
{
	return m_dexterityPoints;
}

int Actor::getSleepTime() const
{
	return m_sleepTime;
}

bool Actor::decreaseHitPoints(int numberToDecrease) // returns true if actor is still alive
{
	m_hitPoints = m_hitPoints - numberToDecrease;
	if (m_hitPoints <= 0)
		return false;
	return true;
}

bool Actor::isAlive() const
{
	if (m_hitPoints <= 0)
		return false;
	return true;
}

void Actor::setSleepTime(int sleepTime)
{
	m_sleepTime = sleepTime;
}

//	Inventory &getInventory(char itemType) const; // should have set inventory/add to inventory
