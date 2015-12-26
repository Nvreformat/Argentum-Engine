#include "character.h"
#include "drawableentity.h"
#include "engine.h"
#include "map.h"
#include <map>
#include <stdlib.h>
#include <iostream>

using namespace std;

Character::Character()
{
	Name = GraphicText(string(""), sf::Vector2f(0, 0), sf::Color(50, 50, 200), 1);
	Chat = Dialog(string(""), sf::Vector2f(0, 0), sf::Color(255, 255, 255), 1);
}

void Character::SetBody(int Head, int Torso, int Helmet, int Weapon, int Shield)
{
	this->BodyIndex[HEAD] = Head;
	this->BodyIndex[TORSO] = Torso;
	this->BodyIndex[HELMET] = Helmet;
	this->BodyIndex[WEAPON] = Weapon;
	this->BodyIndex[SHIELD] = Shield;

	for (int Part = 0; Part < 5; Part++)
	{
		for (int Heading = 0; Heading < 4; Heading++)
		{
			Body[Part][Heading] = DrawableEntity(Engine.Graphics.GetAnimation(Part, BodyIndex[Part], Heading), true, false);
		}
	}

	UpdatePositions();
}

void Character::SetPosition(int X, int Y)
{
	Engine.Map.GetData(Position.X, Position.Y).CharIndex = 0;

	Position.X = X;
	Position.Y = Y;

	Engine.Map.GetData(Position.X, Position.Y).CharIndex = Index;

	MoveOffset.X = 0;
	MoveOffset.Y = 0;

	SetMoving(false);

	UpdatePositions();
}

void Character::SetMoving(bool Moving)
{
	this->Moving = Moving;

	for (int Part = 0; Part < 5; Part++)
	{
		for (int Heading = 0; Heading < 4; Heading++)
		{
			Body[Part][Heading].Animated = Moving;

			if (!Moving)
				Body[Part][Heading].CurrentFrame = 0;
		}
	}
}

void Character::UpdatePositions()
{
	if (Index == -1)
		return;

	int ScreenX = Position.X * 32;
	int ScreenY = Position.Y * 32;

	for (int Part = 0; Part < 5; Part++)
	{
		for (int Heading = 0; Heading < 4; Heading++)
		{
			DrawableEntity& Entity = Body[Part][Heading];

			switch(Part)
			{
				case HEAD:
				case HELMET:
				{
					DrawableEntity& Torso = Body[TORSO][Heading];

					Entity.SetOrigin(16 - (Entity.GetSize().width / 2), -(Torso.GetSize().height / 2));

					break;
				}
				case TORSO:
				case WEAPON:
				case SHIELD:
				{
					Entity.SetOrigin(16 - (Entity.GetSize().width / 2), -(Entity.GetSize().height / 2) + 8);

					break;
				}
			}

			Entity.SetPosition(ScreenX + (int) MoveOffset.X, ScreenY + (int) MoveOffset.Y);
		}
	}

	Name.SetPosition(ScreenX + MoveOffset.X - 16, ScreenY + MoveOffset.Y - 17);
	Chat.SetPosition(ScreenX + MoveOffset.X - 16, ScreenY + MoveOffset.Y - 90);
}

void Character::SetDialog(string Text, int R, int G, int B)
{
	Chat.SetColor(sf::Color(R, G, B));
	Chat.SetText(Text);
	Chat.Show();

	UpdatePositions();
}

Dimension Character::GetAddXYFromDirection(int Direction)
{
	Dimension Return;

	switch(Direction)
	{
	case NORTH:
		Return.Y = -1;
		break;
	case EAST:
		Return.X = 1;
		break;
	case SOUTH:
		Return.Y = 1;
		break;
	case WEST:
		Return.X = -1;
		break;
	}
	
	return Return;
}

void Character::MoveTo(int Dir)
{
	Dimension Add = GetAddXYFromDirection(Dir);

	int NewX = Position.X + Add.X;
	int NewY = Position.Y + Add.Y;

	if (Engine.Map.IsLegalPos(NewX, NewY))
	{
		Engine.Map.GetData(NewX, NewY).CharIndex = Index;
		Engine.Map.GetData(Position.X, Position.Y).CharIndex = 0;

		Position.X += Add.X;
		Position.Y += Add.Y;

		MoveOffset.X = 32 * -Add.X;
		MoveOffset.Y = 32 * -Add.Y;

		MovingDirection = (Heading) Dir;

		SetMoving(true);
	}
}

void Character::MoveTo(int X, int Y)
{
	int AddX = X - Position.X;
	int AddY = Y - Position.Y;
	int Dir = -1;

	if (AddX > 0)
	{
		Dir = EAST;
		AddX = 1;
		AddY = 0;
	}
	else if (AddX < 0)
	{
		Dir = WEST;
		AddX = -1;
		AddY = 0;
	}
	else if (AddY < 0)
	{
		Dir = NORTH;
		AddY = -1;
		AddX = 0;
	}
	else if (AddY > 0)
	{
		Dir = SOUTH;
		AddY = 1;
		AddX = 0;
	}

	if (Dir != -1)
	{
		Engine.Map.GetData(X, Y).CharIndex = Index;
		Engine.Map.GetData(Position.X, Position.Y).CharIndex = 0;

		Position.X = X;
		Position.Y = Y;

		MoveOffset.X = 32 * -AddX;
		MoveOffset.Y = 32 * -AddY;

		MovingDirection = (Heading) Dir;
		Direction = (Heading) Dir;	

		SetMoving(true);
	}
}

void Character::DoUpdates()
{
	if (Moving)
	{
		Dimension Add = GetAddXYFromDirection(MovingDirection);

		MoveOffset.X += 12 * Add.X * Engine.Renderer.TicksPerFrame;
		MoveOffset.Y += 12 * Add.Y * Engine.Renderer.TicksPerFrame;
		
		if ((MoveOffset.X <= 0 && Add.X == -1) || (MoveOffset.X >= 0 && Add.X == 1) || (MoveOffset.Y <= 0 && Add.Y == -1) || (MoveOffset.Y >= 0 && Add.Y == 1))
		{
			MoveOffset.X = 0;
			MoveOffset.X = 0;

			SetMoving(false);
		}

		UpdatePositions();
	}
}

void Character::Draw()
{
	Body[TORSO][Direction].Draw();
	if (BodyIndex[HEAD] != 2)
		Body[HEAD][Direction].Draw();
	if (BodyIndex[HELMET] != 2)
		Body[HELMET][Direction].Draw();
	if (BodyIndex[WEAPON] != 2)
		Body[WEAPON][Direction].Draw();
	if (BodyIndex[SHIELD] != 2)
		Body[SHIELD][Direction].Draw();

	Name.Draw();
	Chat.Draw();
}

bool Character::IsMoving()
{
	return Moving;
}

Heading Character::GetHeading()
{
	return Direction;
}

void Character::SetHeading(Heading Direction)
{
	this->Direction = Direction;
}

std::string Character::GetName()
{
	return Name.GetText();
}

void Character::SetName(std::string Name)
{
	this->Name.SetText(Name);
}

Dimension Character::GetOffset()
{
	return MoveOffset;
}

void Character::SetPosition(Dimension Position)
{
	SetPosition(Position.X, Position.Y);
}

Dimension Character::GetPosition()
{
	return Position;
}

void Character::RemoveDialog()
{
	Chat.Hide();
}

