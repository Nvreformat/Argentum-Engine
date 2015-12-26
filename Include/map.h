#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "graphics.h"
#include <drawableentity.h>

struct WorldPosition
{
	int X = 0;
	int Y = 0;
	int Map = 0;
};

struct MapBlock
{
	DrawableEntity Layers[4];
	DrawableEntity Object;
    int CharIndex;
    
    int NPCIndex;
    WorldPosition TileExit;
    bool Blocked;
    
    int Trigger;
    
    void Zero()
    {
    	CharIndex = 0;
    	Blocked = false;
    	Trigger = 0;
    	Object = DrawableEntity();
    	Layers[0] = DrawableEntity();
    	Layers[1] = DrawableEntity();
    	Layers[2] = DrawableEntity();
    	Layers[3] = DrawableEntity();
    }
};

struct MapSystem
{
	MapBlock Data[100][100];

	MapBlock& GetData(int X, int Y);
	void SetData(int X, int Y, MapBlock Block);

	void Load(int MapIndex);
	bool IsLegalPos(int X, int Y);
	bool IsThereWater(int X, int Y);
};

#endif
