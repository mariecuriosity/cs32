#ifndef SCROLLS_INCLUDED
#define SCROLLS_INCLUDED

#include "GameObjects.h"
#include "constants.h"


class Scrolls : public GameObjects
{
public:
	Scrolls(Dungeon * d, Actor * a, string scrollType);
	virtual string read() = 0;
	bool canRead() const;
	void setAsRead();
private:
	bool m_canRead;
};


#endif SCROLLS_INCLUDED