#ifndef GAME_OBJECTS_INCLUDED
#define GAME_OBJECTS_INCLUDED

#include "utilities.h"
#include "Dungeon.h"

class Actor;

class GameObjects
{
public:
	GameObjects(Dungeon*d, Actor * a, string itemType); //pickedUp is true if initialized by an actor. actor is nullptr if on dungeon
	void setRow(int r);
	void setCol(int c);
	virtual ~GameObjects();
	bool isPickedUp() const;
	void pickUpItem(Actor * a); //pointers to item and actor that picks up
	void dropItem(); //pointers to item and dungeon
	Actor * getActor() const;
	int getRow() const;
	int getCol() const;
	void setHidden();
	string getObjectType() const;
	Dungeon * dungeon() const;
private:
	bool m_display;
	void initializeSpot();
	Dungeon* m_dungeon;
	Actor * m_actor;
	int m_row;
	int m_col;
	string m_objectType;
};

#endif GAME_OBJECTS_INCLUDED