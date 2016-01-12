#include <cstdlib>
#include "Dungeon.h"
#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include "Bogeymen.h"
#include "Snakewomen.h"
#include "Dragons.h"
#include "Goblins.h"
#include "GameObjects.h"
#include "ShortSword.h"
#include "Mace.h"
#include "LongSword.h"
#include "MagicAxe.h"
#include "MagicFang.h"
#include "Scrolls.h"
#include "ScrollOfEnhanceDexterity.h"
#include "ScrollOfEnhanceHealth.h"
#include "ScrollOfImproveArmor.h"
#include "ScrollOfRaiseStrength.h"
#include "ScrollOfTeleportation.h"
#include "Idol.h"

Dungeon::Dungeon(int level)
{
	m_nLevel = level;
	m_nMonsters = 0;
	m_player = nullptr;
	for (int i = 0; i < LEVEL_ROWS; ++i)
	{
		for (int j = 0; j < LEVEL_COLS; ++j)
		{
			m_level[i][j] = "#";
		}
	}
	addRooms();
	m_goblinSmellDistance = 0;
	m_exitRow = 0;
	m_exitCol = 0;
	m_idol = nullptr;
}

Dungeon::Dungeon(int level, Player * p) //alternative constructor when player already exists... aka levels 1-4
{
	m_nLevel = level;
	m_nMonsters = 0;
	for (int i = 0; i < LEVEL_ROWS; ++i)
	{
		for (int j = 0; j < LEVEL_COLS; ++j)
		{
			m_level[i][j] = "#";
		}
	}
	addRooms();
	m_player = p;
	p->initializeSpot();
	p->copyItems(this);
	m_goblinSmellDistance = 0;
	m_exitRow = 0;
	m_exitCol = 0;

}

Dungeon::~Dungeon()
{
	for (int i = 0; i < m_nMonsters; ++i)
		delete m_monsters[i];
	delete m_player;
	for (int i = 0; i < m_nObjects; ++i)
		delete m_objects[i];
	//delete[] m_level;
}

void Dungeon::printDungeon(string msg) const
{
	char grid[LEVEL_ROWS][LEVEL_COLS];
	int r, c;

	// Fill the grid with dots
	for (r = 0; r < LEVEL_ROWS; r++)
	{
		for (c = 0; c < LEVEL_COLS; c++)
		{
			if (m_level[r][c] == ">")
				grid[r][c] = '>';
			else if (m_level[r][c] == "#")
				grid[r][c] = '#';
			else
				grid[r][c] = ' ';
		}
	}

	for (int l = 0; l < m_nObjects; ++l)
	{
		if (!m_objects[l]->isPickedUp())
		{

			Weapons * w = dynamic_cast<Weapons*>(m_objects[l]);
			if (w != nullptr)
				grid[m_objects[l]->getRow()][m_objects[l]->getCol()] = ')';
			else
			{
				Scrolls * s = dynamic_cast<Scrolls*>(m_objects[l]);
				if (s != nullptr && s->canRead())
					grid[m_objects[l]->getRow()][m_objects[l]->getCol()] = '?';
				else
				{
					grid[m_objects[l]->getRow()][m_objects[l]->getCol()] = '&';
				}
			}
		}
	}

	for (int k = 0; k < m_nMonsters; k++)
	{
		if (m_monsters[k]->isAlive())
			grid[m_monsters[k]->getRow()][m_monsters[k]->getCol()] = m_monsters[k]->actorType();
	}

	grid[m_player->getRow()][m_player->getCol()] = '@';

	// Draw the grid
	clearScreen();
	for (r = 0; r < LEVEL_ROWS; r++)
	{
		for (c = 0; c < LEVEL_COLS; c++)
			cout << grid[r][c];
		cout << endl;
	}
	cout << "Dungeon Level: " << m_nLevel << ", Hit points: " << m_player->getHitPoints() << ", Armor: " << m_player->getArmorPoints()
		<< ", Strength: " << m_player->getStengthPoints() << ", Dexterity: " << m_player->getDexterityPoints() << endl;
	if (msg != DEFAULT_STRING)
		cout << endl << msg << endl;
}

string Dungeon::pickUpObject(int r, int c)
{
	if (!noWalls(r, c))
		return DEFAULT_STRING;
	for (int i = 0; i < m_nObjects; ++i)
	{
		if (!m_objects[i]->isPickedUp() && r == m_objects[i]->getRow() && c == m_objects[i]->getCol())
		{
			Idol * s = dynamic_cast<Idol*>(m_objects[i]);
			if (s != nullptr)
				return "You pick up the golden idol\nCongratulations, you won!\nPress q to exit game.\n"; //special output when pick up idol
			m_objects[i]->pickUpItem(m_player);
			m_player->addObject(m_objects[i]);
			
			return "You pick up " + m_objects[i]->getObjectType() + "\n";
		}
	}
	return string();
}

bool Dungeon::isOpen(int r, int c) const //returns if there are no living actors or walls at position
{
	if (m_player != nullptr && m_player->getRow() == r && m_player->getCol() == c)
		return false;
	for (int i = 0; i < m_nMonsters; ++i)
	{
		if (m_monsters[i]->isAlive() && r == m_monsters[i]->getRow() && c == m_monsters[i]->getCol())
			return false;
	}
	if (m_level[r][c] == "#")
		return false;
	return true;
}

bool Dungeon::noWalls(int r, int c) const
{
	if (m_level[r][c] == "#")
		return false;
	return true;
}

void Dungeon::addRooms()
{
	int firstCol = 1;
	bool stack = false;
	for (int i = 0; i < NUM_ROOMS; ++i)
	{
		int rRoom;
		int cRoom = MIN_ROOM_COL + randInt (MAX_ROOM_COL - MIN_ROOM_COL);
		int rUpperLeft;
		int cUpperLeft = firstCol + randInt (4);
		if (stack)
		{
			rRoom = MIN_ROOM_ROW + 1 + randInt ((2 * LEVEL_ROWS / 3 - 2) / 2 - MIN_ROOM_ROW); //special case when stacking, makes sure they won't overlap
			rUpperLeft = (LEVEL_ROWS/2) + randInt (MAX_ROOM_ROW - 3 - rRoom);
		}
		else
		{
			rRoom = MIN_ROOM_ROW + randInt (MAX_ROOM_ROW - MIN_ROOM_ROW)/2;
			rUpperLeft = 1 + randInt ((LEVEL_ROWS-2)/4-1);
		}
		for (int j = rUpperLeft; j < rUpperLeft + rRoom; ++j)
		{
			for (int k = cUpperLeft; k < cUpperLeft + cRoom; ++k)
			{
				m_level[j][k] = " ";
			}
		}
		if (i >0)
			makePathway(stack, rUpperLeft, cUpperLeft); //calls make pathway to make path left to right. will make vertical if stacked.
		if (!stack && rRoom <= (2*LEVEL_ROWS/3 - 2) / 2) //stacks if rooms are on the smaller side. in this case height <= 5
		{
			stack = true;
		}
		else if (stack)
		{
			stack = false;
			firstCol = cUpperLeft + cRoom + 8;
		}
		else
		{
			stack = false;
			firstCol = cUpperLeft + cRoom + 4;
		}
	}
}

void Dungeon::makePathway(bool stack, int rUpperLeft, int cUpperLeft)
{ //makes vertical path if stacked. otherwise, will make horizontal path
	int rPath;
	int cPath;
	if (stack)
	{
		rPath = rUpperLeft;
		cPath = 3+ cUpperLeft + randInt(3);
		for (int i = rPath-1; i > 0; --i)
		{
			if (m_level[i][cPath] == " ")
				break;
			m_level[i][cPath] = " ";
		}
	}
	else
	{
		rPath = ((LEVEL_ROWS - 2) / 4 - 1) + randInt(2);
		cPath = cUpperLeft;
		for (int j = cPath-1; j > 0; --j)
		{
			if (m_level[rPath][j] == " ")
				break;
			m_level[rPath][j] = " ";
		}
	}		
}


void Dungeon::makeExit() //recursive function to make exit
{
	int r = 1 + randInt (LEVEL_ROWS-1);
	int c = 1 + randInt (LEVEL_COLS-1);
	if (isOpen(r, c) && (isOpen(r, c - 1) || isOpen(r, c + 1)) && (isOpen(r - 1, c) || isOpen(r + 1, c)))
	{
		m_level[r][c] = ">";
		m_exitRow = r;
		m_exitCol = c;
	}
	else
		makeExit();
	return;
}

int Dungeon::getExitRow() const
{
	return m_exitRow;
}

int Dungeon::getExitCol() const
{
	return m_exitCol;
}

bool Dungeon::addPlayer()
{
	if (m_player != nullptr)
		return false;
	m_player = new Player(this);
	return true;
}

void Dungeon::setGoblinSmellDistance(int goblinSmellDistance)
{
	m_goblinSmellDistance = goblinSmellDistance;
}

bool Dungeon::addMonster(char monsterType)
{
	if (m_nMonsters == MAX_MONSTERS - 1)
		return false;
	switch (monsterType)
	{
	case M_B:
		m_monsters[m_nMonsters] = new Bogeymen(this);
		break;
	case M_S:
		m_monsters[m_nMonsters] = new Snakewomen(this);
		break;
	case M_D:
		m_monsters[m_nMonsters] = new Dragons(this);
		break;
	case M_G:
		m_monsters[m_nMonsters] = new Goblins(this, m_goblinSmellDistance);
		break;
	}
	
	++m_nMonsters;
	return true;
}

bool Dungeon::noItems(int r, int c) const
{
	for (int i = 0; i < m_nObjects; ++i)
	{
		if (!m_objects[i]->isPickedUp() && r == m_objects[i]->getRow() && c == m_objects[i]->getCol())
		{
			Scrolls * s = dynamic_cast<Scrolls*>(m_objects[i]);
			if (s != nullptr && s->canRead())
				return false;
		}
	}
	if (m_level[r][c] == "#")
		return false;
	return true;

}

GameObjects* Dungeon::addObject(string objectType, Actor * a)
{
	if (m_nObjects == MAX_OBJECTS - 1)
		return nullptr;
	if (objectType == W_SS)
		m_objects[m_nObjects] = new ShortSword(this, a);
	else if (objectType == W_LS)
		m_objects[m_nObjects] = new LongSword(this, a);
	else if (objectType == W_M)
		m_objects[m_nObjects] = new Mace(this, a);
	else if (objectType == W_MA)
		m_objects[m_nObjects] = new MagicAxe(this, a);
	else if (objectType == W_MF)
		m_objects[m_nObjects] = new MagicFang(this, a);
	else if (objectType == S_ED)
		m_objects[m_nObjects] = new SoEnhanceDexterity(this, a);
	else if (objectType == S_EH)
		m_objects[m_nObjects] = new SoEnhanceHealth(this, a);
	else if (objectType == S_IA)
		m_objects[m_nObjects] = new SoImproveArmor(this, a);
	else if (objectType == S_RS)
		m_objects[m_nObjects] = new SoRaiseStrength(this, a);
	else if (objectType == S_T)
		m_objects[m_nObjects] = new SoTeleportation(this, a);
	else if (objectType == "golden idol")
	{
		m_objects[m_nObjects] = new Idol(this);
		m_idol = dynamic_cast<Idol*>(m_objects[m_nObjects]);
	}
	else
		return nullptr;
	++m_nObjects;
	return m_objects[m_nObjects-1];
}

Idol * Dungeon::getIdol() const
{
	return m_idol;
}

GameObjects* Dungeon::addObject(GameObjects* g)
{
	string objectType = g->getObjectType();
	if (m_nObjects == MAX_OBJECTS - 1)
		return nullptr;
	if (objectType == W_SS)
		m_objects[m_nObjects] = g;
	else if (objectType == W_LS)
		m_objects[m_nObjects] = g;
	else if (objectType == W_M)
		m_objects[m_nObjects] = g;
	else if (objectType == W_MA)
		m_objects[m_nObjects] = g;
	else if (objectType == W_MF)
		m_objects[m_nObjects] = g;
	else if (objectType == S_ED)
		m_objects[m_nObjects] = g;
	else if (objectType == S_EH)
		m_objects[m_nObjects] = g;
	else if (objectType == S_IA)
		m_objects[m_nObjects] = g;
	else if (objectType == S_RS)
		m_objects[m_nObjects] = g;
	else if (objectType == S_T)
		m_objects[m_nObjects] = g;
	else if (objectType == "golden idol")
		m_objects[m_nObjects] = g;
	else
		return nullptr;
	++m_nObjects;
	return m_objects[m_nObjects - 1];
}


string Dungeon::moveMonsters()
{
	string output = "";
	for (int i = 0; i < m_nMonsters; ++i)
	{
		if (m_monsters[i]->isAlive())
			output += m_monsters[i]->move();
	}
	return output;
}

Player* Dungeon::player()
{
	return m_player;
}

Monster * Dungeon::monsters(int r, int c) const
{
	for (int i = 0; i < m_nMonsters; ++i)
	{
		if (r == m_monsters[i]->getRow() && c == m_monsters[i]->getCol())
			return m_monsters[i];
	}
	return nullptr;
}