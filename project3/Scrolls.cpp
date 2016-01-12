#include "Scrolls.h"

Scrolls::Scrolls(Dungeon * d, Actor * a, string weaponType)
	:GameObjects(d, a, weaponType)
{
	m_canRead = true;
}

bool Scrolls::canRead() const
{
	return m_canRead;
}

void Scrolls::setAsRead()
{
	m_canRead = false;
}