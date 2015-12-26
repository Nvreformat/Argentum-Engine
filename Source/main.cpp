#include <SFML/Graphics.hpp>
#include "graphics.h"
#include "engine.h"
#include "map.h"
#include "character.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace sf;
using namespace std;

void HandleInput(Character& Char);

int main()
{
	RenderWindow Window(sf::VideoMode(800, 600, 32), "Argentum Online");
	Window.setFramerateLimit(60);
	Window.setVerticalSyncEnabled(true);
	Window.setKeyRepeatEnabled(false);
	
	Engine.Initialize(&Window, 800, 600);
	Engine.Renderer.SetLayerVisible(3, false);
	Engine.Map.Load(34);
	
	// Create Character
	Character& Char = Engine.Entities.AddCharacter(1); // We choose an ID for our character. In this case, we use 1
	Char.SetBody(8, 89, 2, 13, 5);
	Char.SetName("Nvreformat");
	Char.SetHeading((Heading) 0);
	Char.SetPosition(45, 50);

	while (Window.isOpen())
	{
		Window.clear();

		Event Event;
		while (Window.pollEvent(Event))
		{
			if (Event.type == Event::Closed)
			{
				Window.close();
			}
		}

		HandleInput(Char);

		Engine.Update();
		
		Dimension Position = Char.GetPosition();
		Dimension Offset = Char.GetOffset();

		Engine.Renderer.SetCameraPosition((Position.X * 32) + Offset.X, (Position.Y * 32) + Offset.Y);

		Engine.Render();

		Window.display();
	}

	return 0;
}

void HandleInput(Character& Char)
{
	Dimension Position = Char.GetPosition();
	
	if (!Char.IsMoving())
	{
		int MoveX = 0;
		int MoveY = 0;
		int Direction = -1;

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			MoveY = -1;
			Direction = NORTH;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			MoveX = 1;
			Direction = EAST;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			MoveY = 1;
			Direction = SOUTH;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			MoveX = -1;
			Direction = WEST;
		}

		if (Direction > -1)
		{
			Char.SetHeading((Heading) Direction);

			if (Engine.Map.IsLegalPos(Position.X + MoveX, Position.Y + MoveY))
			{
				Char.MoveTo(Direction);
			}
			else
			{
				Char.SetHeading((Heading) Direction);
			}
		}
	}
}
