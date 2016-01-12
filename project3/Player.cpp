#include "Player.h"

Player::Player(Dungeon *d):Actor(d, 20, 2, 2, 2, W_SS)
{
	m_nItems = 0;
	addItem(W_SS);
	m_currItem = m_inventory[0];
}

Player::~Player()
{

}

void Player::increaseMaxHitPoints(int amount)
{
	m_maxHitPoints += amount;
}

bool Player::copyItems(Dungeon * d)
{
	switchDungeon(d);
	initializeSpot();
	for (int i = 1; i < m_nItems; ++i)
	{
		dungeon()->addObject(m_inventory[i]);
	}
	return true;
}

void Player::addHitPoints(double prob)
{
	if (prob <= 0 || m_maxHitPoints >= getHitPoints())
		return;
	if (trueWithProbability(prob))
		Actor::addHitPoints();
}


void Player::printInventory()
{
	clearScreen();
	cout << "Inventory:" << endl;
	int j = 0;
	for (int i = 0; i < m_nItems; ++i)
	{
		if (m_inventory[i]->isPickedUp())
		{
			Scrolls * s = dynamic_cast<Scrolls*>(m_inventory[i]); //prints the choices of all valid items (not read)
			if (s != nullptr && s->canRead())
			{
				cout << " " << static_cast<char>(j + 'a') << ".   " << m_inventory[i]->getObjectType() << endl;
				++j;
			}
			else if (s == nullptr)
			{
				cout << " " << static_cast<char>(j + 'a') << ".   " << m_inventory[i]->getObjectType() << endl;
				++j;
			}
		}
	}
	char command = _getch();
	int k = 0;
	for (int i = 0; i < m_nItems; ++i)
	{
		if (m_inventory[i]->isPickedUp())
		{
			Scrolls * s = dynamic_cast<Scrolls*>(m_inventory[i]);
			Weapons * w = dynamic_cast<Weapons*>(m_inventory[i]);
			Idol * iD = dynamic_cast<Idol*>(m_inventory[i]);
			if (command == static_cast<char>(k + 'a')) //determines which choice is correct
			{
				if (w != nullptr)
				{
					m_currItem = m_inventory[i];
					dungeon()->printDungeon("You are wielding " + m_currItem->getObjectType() + "\n");
					break;
				}
				else if (s != nullptr && s->canRead())
				{
					dungeon()->printDungeon(s->read());
					break;
				}
				else if (iD != nullptr)
				{
					dungeon()->printDungeon("You pick up the golden idol\nCongratulations, you won!\npress q to exit game.\n");
					break;
				}
			}
			if (s != nullptr && s->canRead())
				++k;
			else if (s == nullptr)
				++k;
		}
	}
	char end = _getch(); //requires an input of key to return back to game
	return;
}

string Player::move(char dir)
{
	int sleepTime = getSleepTime();
	if (sleepTime > 0)
	{
		setSleepTime(sleepTime - 1);
		return string();
	}
	addHitPoints(PLAYERS_HP_REGAIN_PROB);
	Actor::setOneAway(dir);
	return attack(dir); //will return empty string if did not attack.
}

char Player::actorType()
{
	return M_P;
}

bool Player::addObject(GameObjects * object)
{
	if (m_nItems == PLAYER_MAX_INVENTORY - 1)
		return false;
	m_inventory[m_nItems] = object;
	++m_nItems;
	return true;
}

string Player::attack(char dir)
{
	int r = getRow();
	int c = getCol();
	switch (dir)
	{
	case ARROW_UP:
		--r;
		break;
	case ARROW_DOWN:
		++r;
		break;
	case ARROW_LEFT:
		--c;
		break;
	case ARROW_RIGHT:
		++c;
		break;
	}
	Monster * m = dungeon()->monsters(r, c); //only attacks if monster is in the position in front of player
	if (m == nullptr || !m->isAlive())
		return string();
	Weapons * w = dynamic_cast<Weapons*>(m_currItem);
	if (w != nullptr)
		return w->actionString(m);
	else
	{
		Scrolls * s = dynamic_cast<Scrolls*>(m_currItem); //not necessary... I changed it so that a scroll can never be the current item
		if (s->canRead())
			return s->read();
	}
	return string();
}

bool Player::addItem(string item)
{
	if (m_nItems == PLAYER_MAX_INVENTORY - 1)
		return false;
	m_inventory[m_nItems] = dungeon()->addObject(item, this);
	++m_nItems;
	return true;
}
