// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "constants.h"

// You may add data members and other member functions to this class.
class Dungeon;

class Game
{
public:
	Game(int goblinSmellDistance);
	~Game();
	void play();
private:
	int m_goblinSmellDistance;
	Dungeon* m_dungeon[5];
	char randomMonster(int level);
	string randomObject();
	int m_level;
	void addLevel();
};

#endif // GAME_INCLUDED
