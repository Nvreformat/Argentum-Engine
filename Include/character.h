#ifndef CHARACTER_H
#define CHARACTER_H

#include "map.h"
#include <vector>
#include "drawableentity.h"
#include "graphicfont.h"
#include <string>
#include "misc.h"
#include "dialog.h"

enum Heading
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3,
};

enum BodyPart
{
	HEAD = 0,
	TORSO = 1,
	HELMET = 2,
	WEAPON = 3,
	SHIELD = 4,
};

class Character
{
private:
	Dialog Chat;
	GraphicText Name;
	Dimension Position;
	bool Active;
	Heading Direction;
	Heading MovingDirection;
	int BodyIndex[5];

	DrawableEntity Body[5][4];
	DrawableEntity FX;

	bool Criminal = false;
	bool Attackable = true;
	bool Moving = false;
	Dimension MoveOffset;
	bool Dead = false;

	void SetMoving(bool Moving);
	void UpdatePositions();

public:
	int Index = -1;

	Character();

	void SetBody(int Head, int Torso, int Helmet, int Weapon, int Shield);
	void SetPosition(int X, int Y);
	void SetPosition(Dimension Position);
	Dimension GetPosition();
	bool IsMoving();
	Heading GetHeading();
	void SetHeading(Heading Direction);
	Dimension GetOffset();
	std::string GetName();
	void SetName(std::string Name);
	void MoveTo(int Dir);
	void MoveTo(int X, int Y);

	void DoUpdates();
	void Draw();
	void SetDialog(std::string Text, int R, int G, int B);
	void RemoveDialog();
	static Dimension GetAddXYFromDirection(int Direction);
};

#endif
