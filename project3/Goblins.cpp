#include "Goblins.h"
#include "Actor.h"

//Dungeon *d, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, string startingWeapon, int smellDistance
Goblins::Goblins(Dungeon * d, int smellDistance) :Monster(d, 15 + randInt(6), 1, 3, 1, W_SS, 15, GOBLINS_HP_REGAIN_PROB,1/3)
{
	m_smellDistance = smellDistance;
}

Goblins::~Goblins()
{

}

char Goblins::actorType()
{
	return M_G;
}

/*
Coord Goblins::smellPath(Coord current, Coord *maze[][LEVEL_COLS]) const
{
	int r = current.r();
	int c = current.c();
	int d = current.d();
	char dir = current.dir();
	char directionToMove = dir;
	int p_r = dungeon()->player()->getRow();
	int p_c = dungeon()->player()->getCol();
	if(maze[r][c]->d() > d)
		maze[r][c] = &current;
	if (r == p_r && c == p_c)
		return *maze[r][c];
	if (maze[r][c]->d() < d || d > m_smellDistance)
		return Coord(r, c, 100000, 'f');
	Coord outputCoord = Coord(r, c, 100000, 'f');
	if (current.d() == 0)
	{
		if (dungeon()->noWalls(r + 1, c))
		{
			Coord temp = smellPath(Coord(r + 1, c, 1, ARROW_DOWN), maze);
			if (temp.dir() != 'f' && outputCoord.d() > temp.dir())
				outputCoord = temp;
		}
		if (dungeon()->noWalls(r - 1, c))
		{
			Coord temp = smellPath(Coord(r - 1, c, 1, ARROW_UP), maze);
			if (temp.dir() != 'f' && outputCoord.d() > temp.dir())
				outputCoord = temp;
		}
		if (dungeon()->noWalls(r, c + 1))
		{
			Coord temp = smellPath(Coord(r, c + 1, 1, ARROW_RIGHT), maze);
			if (temp.dir() != 'f' && outputCoord.d() > temp.dir())
				outputCoord = temp;
		}
		if (dungeon()->noWalls(r, c - 1))
		{
			Coord temp = smellPath(Coord(r, c - 1, 1, ARROW_LEFT), maze);
			if (temp.dir() != 'f' && outputCoord.d() > temp.dir())
				outputCoord = temp;
		}
	}
	else
	{
		if (dungeon()->noWalls(r + 1, c))
		{
			Coord temp = smellPath(Coord(r + 1, c, d + 1, dir), maze);
			if (temp.dir() != 'f' && outputCoord.d() > temp.dir())
				outputCoord = temp;
		}
		if (dungeon()->noWalls(r - 1, c))
		{
			Coord temp = smellPath(Coord(r - 1, c, d + 1, dir), maze);
			if (temp.dir() != 'f' && outputCoord.d() > temp.dir())
				outputCoord = temp;
		}
		if (dungeon()->noWalls(r, c + 1))
		{
			Coord temp = smellPath(Coord(r, c + 1, d + 1, dir), maze);
			if (temp.dir() != 'f' && outputCoord.d() > temp.dir())
				outputCoord = temp;
		}
		if (dungeon()->noWalls(r, c - 1))
		{
			Coord temp = smellPath(Coord(r, c - 1, d + 1, dir), maze);
			if (temp.dir() != 'f' && outputCoord.d() > temp.dir())
				outputCoord = temp;
		}
	}
	return outputCoord;
}


Coord Goblins::smellPath(char maze[][LEVEL_COLS])
{
	Dungeon * dd = dungeon();
	int m_r = getRow();
	int m_c = getCol();
	int p_r = dd->player()->getRow();
	int p_c = dd->player()->getCol();
	queue <Coord> toEvaluate;
	Coord current(m_r, m_c, 0, 'f');
	bool failed = false;
	while (current.r() != p_r && current.c() != p_c)
	{
		int r = current.r();
		int c = current.c();
		int d = current.d();
		char dir = current.dir();
		maze[r][c] = 'D';
		if (d == 0)
		{
			if (maze[r + 1][c] == EMPTY_SPACE && dd->noWalls(r + 1, c))
				toEvaluate.push(Coord(r + 1, c, d + 1, ARROW_DOWN));
			if (maze[r - 1][c] == EMPTY_SPACE && dd->noWalls(r - 1, c))
				toEvaluate.push(Coord(r - 1, c, d + 1, ARROW_UP));
			if (maze[r][c + 1] == EMPTY_SPACE && dd->noWalls(r, c + 1))
				toEvaluate.push(Coord(r, c + 1, d + 1, ARROW_RIGHT));
			if (maze[r][c - 1] == EMPTY_SPACE && dd->noWalls(r, c - 1))
				toEvaluate.push(Coord(r, c - 1, d + 1, ARROW_LEFT));
		}
		else
		{
			if (maze[r + 1][c] == EMPTY_SPACE && dd->noWalls(r + 1, c))
				toEvaluate.push(Coord(r + 1, c, d + 1, dir));
			if (maze[r - 1][c] == EMPTY_SPACE && dd->noWalls(r - 1, c))
				toEvaluate.push(Coord(r - 1, c, d + 1, dir));
			if (maze[r][c + 1] == EMPTY_SPACE && dd->noWalls(r, c + 1))
				toEvaluate.push(Coord(r, c + 1, d + 1, dir));
			if (maze[r][c - 1] == EMPTY_SPACE && dd->noWalls(r, c - 1))
				toEvaluate.push(Coord(r, c - 1, d + 1, dir));
		}
		if (toEvaluate.empty())
		{
			failed = true;
			break;
		}
		current = toEvaluate.front();
		toEvaluate.pop();
	}
	if (failed || current.d() > m_smellDistance)
		return DEFAULT_COORD;
	else
		return current;
}


string Goblins::move()
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
		Player * p = dungeon()->player();
		Coord* maze[LEVEL_ROWS][LEVEL_COLS];
		for (int i = 0; i < LEVEL_ROWS; ++i)
			for (int j = 0; j < LEVEL_COLS; ++j)
				maze[i][j] = &Coord(i,j,100000,'f');
		Coord c = smellPath(Coord(getRow(), getCol(), 0, 'f'), maze);
		setOneAway(c.dir());
		return string();
	}
}
*/