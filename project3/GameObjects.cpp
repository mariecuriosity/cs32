#include "GameObjects.h"
#include "Actor.h"

GameObjects::GameObjects(Dungeon * d, Actor * a, string itemType)
{
	if (d == nullptr)
		exit(1);
	m_objectType = itemType;
	m_dungeon = d;
	m_actor = a;
	m_display = true;
	initializeSpot();
}

GameObjects::~GameObjects()
{

}

void GameObjects::setRow(int r)
{
	m_row = r;
}

void GameObjects::setCol(int c)
{
	m_col = c;
}


Dungeon * GameObjects::dungeon() const
{
	return m_dungeon;
}

void GameObjects::setHidden()
{
	m_display = false;
}

void GameObjects::initializeSpot()
{
	int r = 1 + randInt(LEVEL_ROWS - 1);
	int c = 1 + randInt(LEVEL_COLS - 1);
	if (m_dungeon->noWalls(r, c) && (m_dungeon->noWalls(r, c - 1) || m_dungeon->noWalls(r, c + 1))
		&& (m_dungeon->noWalls(r - 1, c) || m_dungeon->noWalls(r + 1, c)))
	{
		m_row = r;
		m_col = c;
	}
	else
		initializeSpot();
	return;
}

string GameObjects::getObjectType() const
{
	return m_objectType;
}


int GameObjects::getRow() const
{
	return m_row;
}

int GameObjects::getCol() const
{
	return m_col;
}

Actor * GameObjects::getActor() const
{
	return m_actor;
}

bool GameObjects::isPickedUp() const
{
	if (m_actor == nullptr)
		return false;
	else
		return true;
}

void GameObjects::pickUpItem(Actor* a)
{
	if (isPickedUp())
		return; //already picked up by someone
	m_actor = a;
}

void GameObjects::dropItem()
{
	m_actor = nullptr;
}

