#include "Lib/BufferedFile.h"
#include "graphics.h"
#include <SFML/Graphics.hpp>
#include <map.h>
#include <engine.h>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace sf;

void MapSystem::Load(int MapIndex)
{
	printf("Loading map %s\n", ("Maps/Mapa" + to_string(MapIndex) + ".map").c_str());
	BufferedFile File = BufferedFile("Resources/Maps/Mapa" + to_string(MapIndex) + ".map", "rb");
	
	uint16_t MapVersion = File.Read(&MapVersion);
	MapHeader Header = File.Read(&Header);
	
	uint16_t TempInt;
	File.Read(&TempInt);
	File.Read(&TempInt);
	File.Read(&TempInt);
	File.Read(&TempInt);
	
	for (int Y = 0; Y < 100; Y++)
	{
		for (int X = 0; X < 100; X++)
		{
			Data[X][Y].Zero();

			uint8_t Flags = File.Read(&Flags);
			
			Data[X][Y].Blocked = Flags & 1;
			
			uint16_t GrhIndex1 = File.Read(&GrhIndex1);
			
			Data[X][Y].Layers[0] = DrawableEntity(GrhIndex1, true, true);
			Data[X][Y].Layers[0].SetPosition(X * 32, Y * 32);
			
			//Layer 2 used?
			if (Flags & 2)
			{
				uint16_t GrhIndex2 = File.Read(&GrhIndex2);
				
				Data[X][Y].Layers[1] = DrawableEntity(GrhIndex2, true, false);
			}
			Data[X][Y].Layers[1].SetPosition(X * 32, Y * 32);
			
			//Layer 3 used?
			if (Flags & 4)
			{
				uint16_t GrhIndex3 = File.Read(&GrhIndex3);
				
				Data[X][Y].Layers[2] = DrawableEntity(GrhIndex3, true, true);
			}
			Data[X][Y].Layers[2].SetPosition(X * 32, Y * 32);
			
			//Layer 4 used?
			if (Flags & 8)
			{
				uint16_t GrhIndex4 = File.Read(&GrhIndex4);
				
				Data[X][Y].Layers[3] = DrawableEntity(GrhIndex4, true, false);
			}
			Data[X][Y].Layers[3].SetPosition(X * 32, Y * 32);
			
			//Triggers
			if (Flags & 16)
			{
				uint16_t Trigger = File.Read(&Trigger);

				Data[X][Y].Trigger = Trigger;
			}
			else
			{
				Data[X][Y].Trigger = 0;
			}
		
			Data[X][Y].Object = DrawableEntity();
		}
	}
}

bool MapSystem::IsThereWater(int X, int Y)
{
	if (Data[X][Y].Layers[1].GrhIndex != 0)
		return false;

	if (Data[X][Y].Layers[0].GrhIndex >= 1505 && Data[X][Y].Layers[0].GrhIndex <= 1520)
		return true;

	if (Data[X][Y].Layers[0].GrhIndex >= 5665 && Data[X][Y].Layers[0].GrhIndex <= 5680)
		return true;

	if (Data[X][Y].Layers[0].GrhIndex >= 1505 && Data[X][Y].Layers[0].GrhIndex <= 1520)
		return true;

	return false;
}

bool MapSystem::IsLegalPos(int X, int Y)
{
	if (Data[X][Y].Blocked)
		return false;

	if (Data[X][Y].CharIndex > 0)
		return false;

	if (IsThereWater(X, Y))
		return false;

	return true;
}

MapBlock& MapSystem::GetData(int X, int Y)
{
	return Data[X][Y];
}

void MapSystem::SetData(int X, int Y, MapBlock Block)
{
	Data[X][Y] = Block;
}
