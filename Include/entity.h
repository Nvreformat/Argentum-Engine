#ifndef ENTITY_H
#define ENTITY_H

#include "character.h"

struct EntitySystem
{
	std::map<int, Character> Charlist;

	Character& GetCharacter(int Index);
	Character& AddCharacter(int Index);
	void RemoveCharacter(int Index);

	void DoUpdates();
};



#endif
