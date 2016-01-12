#ifndef DUNGEON_INCLUDED
#define DUNGEON_INCLUDED

using namespace std;
#include "Game.h"
#include "utilities.h"
#include <iostream>
#include "constants.h"

class Actor;
class Player;
class Monster;
class Bogeymen;
class Snakewomen;
class Dragon;
class Goblin;
class GameObjects;
class Idol;

class Dungeon
{
public:
	Dungeon(int level);
	Dungeon(int level, Player * p); //alternative constructor when player already exists... aka levels 1-4
	~Dungeon();
	void printDungeon(string msg) const;
	bool isOpen(int r, int c) const;
	bool noItems(int r, int c) const;
	bool addPlayer();
	bool addMonster(char monsterType);
	GameObjects * addObject(string objectType, Actor * a); //returns null if couldn't add
	GameObjects * addObject(GameObjects * g);
	string pickUpObject(int r, int c);
	string moveMonsters();
	bool noWalls(int r, int c) const;
	Player * player();
	Monster * monsters(int r, int c) const;
	void setGoblinSmellDistance(int goblinSmellDistance);
	void makeExit();
	int getExitRow() const;
	int getExitCol() const;
	Idol * getIdol() const;
private:
	Idol * m_idol;
	int m_exitRow;
	int m_exitCol;
	int m_nLevel;
	int m_goblinSmellDistance;
	char* m_level[LEVEL_ROWS][LEVEL_COLS];
	void addRooms();
	void makePathway(bool stack, int rUpperLeft, int cUpperLeft);
	Player * m_player;
	int m_nMonsters;
	Monster * m_monsters[MAX_MONSTERS];
	GameObjects * m_objects[MAX_OBJECTS];
	int m_nObjects;
};

#endif DUNGEON_INCLUDED
