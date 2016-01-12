#include "Monster.h"
#include "Player.h"

Monster::Monster(Dungeon * d, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, string startingWeapon,
	int smellDistance, double hpProb, double dropProb)
	:Actor( d, hitPoints, armorPoints, strengthPoints, dexterityPoints, startingWeapon)
{
	m_smellDistance = smellDistance;
	m_hpProb = hpProb;
	m_object = dungeon()->addObject(startingWeapon, this);
	m_dropProb = dropProb;
}

Monster::~Monster()
{

}

bool Monster::isAlive()
{
	if (!Actor::isAlive())
	{
		dropItem(m_dropProb);
		return false;
	}
	return true;
}

void Monster::dropItem(double prob)
{
	int r = getRow();
	int c = getCol();
	if (dungeon()->noItems(r, c))
	{
		if (actorType() == M_B && trueWithProbability(prob))
		{
			GameObjects * o = dungeon()->addObject(W_MA, nullptr);
			o->setRow(r);
			o->setCol(c);
		}
		else if (actorType() == M_S && trueWithProbability(prob))
		{
			GameObjects * o = dungeon()->addObject(W_MF, nullptr);
			o->setRow(r);
			o->setCol(c);
		}
		else if (actorType() == M_D && trueWithProbability(prob))
		{
			GameObjects * o = dungeon()->addObject(SCROLL_LIST[randInt(5)], nullptr);
			o->setRow(r);
			o->setCol(c);
		}
		else if (actorType() == M_G && trueWithProbability(prob))
		{
			GameObjects * o = dungeon()->addObject(GOBLIN_DROP_LIST[randInt(2)], nullptr);
			o->setRow(r);
			o->setCol(c);
		}
	}
}

char Monster::playerNearBy()
{
	if (m_smellDistance == 0)
		return 'f';
	Player* p = dungeon()->player();
	Dungeon* d = dungeon();
	if (p == nullptr)
	{
		cout << "Player not initialized. something is very wrong..." << endl;
		return(1);
	}
	int r = getRow();
	int c = getCol();
	int y_diff = r - p->getRow();
	int x_diff = c - p->getCol();
	if (abs(y_diff) + abs(x_diff) > m_smellDistance)
		return 'f';
	else if (abs(x_diff) == abs(y_diff))
	{
		if (x_diff < 0) //move right
		{
			if (d->isOpen(r, c + 1))
				return ARROW_RIGHT;
			else if (y_diff < 0) //move down
				return ARROW_DOWN;
			else
				return ARROW_UP;
		}
		else // x_diff >= 0
		{
			if (d->isOpen(r, c - 1))
				return ARROW_LEFT;
			else if (y_diff < 0)
				return ARROW_DOWN;
			else
				return ARROW_UP;
		}
	}
	else if (abs(x_diff) < abs(y_diff)) //greater distance of movement direction is prioritized
	{
		if (y_diff < 0 && (d->isOpen(r + 1, c) || x_diff == 0))
			return ARROW_DOWN;
		else if (y_diff > 0 && (d->isOpen(r - 1, c) || x_diff == 0))
			return ARROW_UP;
		else if (x_diff < 0)
				return ARROW_RIGHT;
		else if (x_diff > 0)
			return ARROW_LEFT;
	}
	else
	{
		if (x_diff < 0 && (d->isOpen(r, c + 1) || y_diff == 0))
			return ARROW_RIGHT;
		else if (x_diff > 0 && (d->isOpen(r, c - 1) || y_diff == 0))
			return ARROW_LEFT;
		else if (y_diff < 0)
			return ARROW_DOWN;
		else if (y_diff > 0)
			return ARROW_UP;
	}
	return 'f';
}

bool Monster::isNextTo()
{
	Player * p = dungeon()->player();
	int r_diff = abs(p->getRow() - getRow());
	int c_diff = abs(p->getCol() - getCol());
	if ((r_diff == 0 && c_diff == 1) || (r_diff == 1 && c_diff == 0))
		return true;
	else
		return false;
}

string Monster::attack()
{
	Weapons * w = dynamic_cast<Weapons*>(m_object);
	if (w == nullptr)
		return string();
	Player * p = dungeon()->player();
	return w->actionString(p);
}


string Monster::move()
{
	int sleep = getSleepTime();
	if (sleep > 0)
	{
		setSleepTime(sleep - 1);
		return string();
	}
	if (isNextTo())
		return attack();
	else
	{
		setOneAway(playerNearBy());
		return string();
	}
}