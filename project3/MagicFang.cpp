#include "MagicFang.h"

MagicFang::MagicFang(Dungeon * d, Actor * a)
	:Weapons(d, a, W_MF)
{
}

string MagicFang::actionString(Actor * m) const
{
	string output = Weapons::actionString(m); //MagicFang can attack and put an Actor to sleep!!!
	if (output == string())
		return output;
	if (trueWithProbability(0.2))
	{
		int sleepTime = 2 + randInt(5);
		int currSleepTime = m->getSleepTime();
		if (sleepTime > currSleepTime)
			m->setSleepTime(sleepTime);
		string actor = actorCharToString(m->actorType());
		output = output.substr(0, output.size() - 2) +", putting " + actor + " to sleep.\n";
	}
	return output;
}
