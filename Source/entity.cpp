#include "entity.h"
#include "engine.h"

Character& EntitySystem::GetCharacter(int Index)
{
	return Charlist[Index];
}

Character& EntitySystem::AddCharacter(int Index)
{
	Charlist[Index] = Character();
	Charlist[Index].Index = Index;
	
	return Charlist[Index];
}

void EntitySystem::RemoveCharacter(int Index)
{
	Character& Char = Charlist[Index];
	Dimension Position = Char.GetPosition();

	Engine.Map.GetData(Position.X, Position.Y).CharIndex = 0;

	Charlist.erase(Index);
}

void EntitySystem::DoUpdates()
{
	for (auto& Entry : Charlist)
	{
		Character& Char = Entry.second;

		Char.DoUpdates();
	}
}
