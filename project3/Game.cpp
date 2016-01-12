// Game.cpp

#include "Game.h"
#include "Dungeon.h"
#include "Player.h"
#include "utilities.h"
#include <iostream>
#include "Idol.h"
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
	m_goblinSmellDistance = goblinSmellDistance;
	m_level = 0;
	m_dungeon[0] = new Dungeon(goblinSmellDistance);
	m_dungeon[0]->addPlayer();
	m_dungeon[0]->setGoblinSmellDistance(m_goblinSmellDistance);
	int m_nMonsters = 2 + randInt(5 * (m_level + 1));
	m_dungeon[0]->makeExit();
	for (int i = 0; i < m_nMonsters; ++i)
	{
		m_dungeon[0]->addMonster(randomMonster(m_level));
	}
	int m_nObjects = 2 + randInt(2);
	for (int j = 0; j < m_nObjects; ++j)
	{
		m_dungeon[0]->addObject(randomObject(), nullptr);
	}
}

Game::~Game()
{
	for(int i = 0; i < m_level; ++i)
		delete m_dungeon[i];
}

void Game::addLevel()
{
	m_level += 1;
	m_dungeon[m_level] = new Dungeon(m_level, m_dungeon[m_level-1]->player());
	m_dungeon[m_level]->setGoblinSmellDistance(m_goblinSmellDistance);
	int m_nMonsters = 2 + randInt(5 * (m_level + 1));
	if (m_level < 4)
		m_dungeon[m_level]->makeExit();
	else
		m_dungeon[m_level]->addObject("golden idol", nullptr);
	for (int i = 0; i < m_nMonsters; ++i)
	{
		m_dungeon[m_level]->addMonster(randomMonster(m_level));
	}
	int m_nObjects = 2 + randInt(2);
	for (int j = 0; j < m_nObjects; ++j)
	{
		m_dungeon[m_level]->addObject(randomObject(), nullptr);
	}
}

string Game::randomObject()
{
	return DUNGEON_OBJECT_LIST[randInt(7)];
}

char Game::randomMonster(int level)
{
	if (level == 0)
	{
		char monsterList[2] = { M_S,M_G };
		return monsterList[randInt(2)];
	}
	else if (level == 1)
	{
		char monsterList[3] = { M_S,M_G,M_B };
		return monsterList[randInt(3)];
	}
	else if (level == 2 || level == 3 || level == 4)
	{
		char monsterList[4] = { M_S,M_G,M_B,M_D };
		return monsterList[randInt(4)];
	}
	else
	{
		cout << "Error! can't have more than 5 levels" << endl;
		exit(1);
	}
}

void Game::play()
{
	Player*p = m_dungeon[m_level]->player();
	string output = DEFAULT_STRING;
	char command = 'X';
	while (command != 'q' && p->isAlive() && m_level < 5) //add monsters
	{
		m_dungeon[m_level]->printDungeon(output);
		string item = DEFAULT_STRING;
		output = "";
		output = m_dungeon[m_level]->moveMonsters();
		command = getCharacter();
		switch (command)
		{
		default:
			continue;
		case '>':
			if (p->getRow() == m_dungeon[m_level]->getExitRow() && p->getCol() == m_dungeon[m_level]->getExitCol())
				addLevel();
			break;
		case 'q':
			exit(0);
		case 'c':
			p->cheat();
			break;
		case ARROW_LEFT:
		case ARROW_RIGHT:
		case ARROW_UP:
		case ARROW_DOWN:
			output = p->move(command) + output;
			break;
		case 'g':
			output = m_dungeon[m_level]->pickUpObject(p->getRow(), p->getCol()) + output;
			break;
		case 'w':
		case 'r':
		case 'i':
			m_dungeon[m_level]->player()->printInventory();
			break;
			/*
		case '&':
			if (m_dungeon[m_level]->getIdol() != nullptr && m_dungeon[m_level]->getIdol()->getRow() == p->getRow()
				&& m_dungeon[m_level]->getIdol()->getCol() == p->getCol())
			{
				output = "You pick up the golden idol\nCongratulations, you won!\npress q to exit game.\n";
				command = getCharacter();
				break;
			}
			continue;
			*/
		}
	}
//	m_dungeon->printDungeon("");
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
