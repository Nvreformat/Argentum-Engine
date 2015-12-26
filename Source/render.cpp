#include "engine.h"
#include "graphics.h"
#include <character.h>
#include <map.h>
#include <string>
#include <stdlib.h>
#include "render.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void RenderSystem::Render()
{
	const Vector2f CameraPosition = GetCameraPosition();
	MapBlock (&MapData)[100][100] = Engine.Map.Data;

	int CameraTileX = CameraPosition.x / 32;
	int CameraTileY = CameraPosition.y / 32;

	int HalfSizeX = (GetSize().X / 32) / 2;
	int HalfSizeY = (GetSize().Y / 32) / 2;
	
	int MinCameraX = CameraTileX - HalfSizeX;
	int MinCameraY = CameraTileY - HalfSizeY;
	int MaxCameraX = CameraTileX + HalfSizeX + 1;
	int MaxCameraY = CameraTileY + HalfSizeY + 1;
	
	if (MinCameraX < 0)
		MinCameraX = 0;
	
	if (MinCameraY < 0)
		MinCameraY = 0;
		
	if (MaxCameraX > 99)
		MaxCameraX = 99;
	
	if (MaxCameraY > 99)
		MaxCameraY = 99;

	if (DrawLayer[0])
	{
		for (int Y = MinCameraY; Y < MaxCameraY + 1; Y++)
		{
			for (int X = MinCameraX; X < MaxCameraX + 1; X++)
			{
				MapData[X][Y].Layers[0].Draw();
			}
		}
	}
	
	if (DrawLayer[1])
	{
		for (int Y = MinCameraY; Y < MaxCameraY + 1; Y++)
		{
			for (int X = MinCameraX; X < MaxCameraX + 1; X++)
			{
				MapData[X][Y].Layers[1].Draw();
			}
		}
	}
	
	int MinCameraX2 = MinCameraX - 5;
	int MinCameraY2 = MinCameraY;
	int MaxCameraX2 = MaxCameraX + 5;
	int MaxCameraY2 = MaxCameraY + 10;

	if (MinCameraX2 < 0)
		MinCameraX2 = 0;

	if (MinCameraY2 < 0)
		MinCameraY2 = 0;

	if (MaxCameraX2 > 99)
		MaxCameraX2 = 99;

	if (MaxCameraY2 > 99)
		MaxCameraY2 = 99;

	if (DrawLayer[2])
	{
		for (int Y = MinCameraY2; Y < MaxCameraY2; Y++)
		{
			for (int X = MinCameraX2; X < MaxCameraX2; X++)
			{
				MapData[X][Y].Object.Draw();
				MapData[X][Y].Layers[2].Draw();

				if (MapData[X][Y].CharIndex > 0)
				{
					Character& Char = Engine.Entities.Charlist[MapData[X][Y].CharIndex];

					Char.Draw();
				}
			}
		}
	}

	if (DrawLayer[3])
	{
		for (int Y = MinCameraY2; Y < MaxCameraY2; Y++)
		{
			for (int X = MinCameraX2; X < MaxCameraX2; X++)
			{
				MapData[X][Y].Layers[3].Draw();
			}
		}
	}
}

void RenderSystem::ShowNextFrame()
{
	static int DisplayFPS = 0;
	
	Buffer.clear(Color::Black);
	Buffer.setView(WorldView);

	Time TimeElapsed = Clock.restart();

	Render();
	Buffer.display();

	Window->draw(RenderSprite);

	ElapsedTime = (double)(TimeElapsed.asMicroseconds()) / 1000;
	TicksPerFrame = ElapsedTime * 0.018;
	DisplayFPS++;
	
	if (DisplayFPS % 100 == 0)
		Window->setTitle(to_string(1000000 / TimeElapsed.asMicroseconds()));
}

void RenderSystem::SetPosition(int X, int Y)
{
	Position = Dimension(X, Y);

	RenderSprite.setPosition(X, Y);
}

Dimension& RenderSystem::GetPosition()
{
	return Position;
}

bool RenderSystem::IsInBounds(int X, int Y)
{
	int X1 = RenderSprite.getPosition().x;
	int Y1 = RenderSprite.getPosition().y;
	int X2 = RenderSprite.getTexture()->getSize().x + X1;
	int Y2 = RenderSprite.getTexture()->getSize().y + Y1;

	if (X < X1 or X > X2 or Y < Y1 or Y > Y2)
		return false;

	return true;
}

void RenderSystem::SetSize(int X, int Y)
{
	Size = Dimension(X, Y);

	Buffer.create(X, Y);
	RenderSprite = Sprite(Buffer.getTexture());

	WorldView.setSize(sf::Vector2f(X, Y));
}

Dimension& RenderSystem::GetSize()
{
	return Size;
}

void RenderSystem::SetCameraPosition(int X, int Y)
{
	WorldView.setCenter(sf::Vector2f(X - 16, Y - 48));
}

const Vector2f RenderSystem::GetCameraPosition()
{
	const Vector2f Center = WorldView.getCenter();
	Vector2f Return = Center;

	Return.x += 16;
	Return.y += 48;

	return Return;
}

void RenderSystem::Initialize(RenderWindow* Window)
{
	this->Window = Window;

	Buffer.setView(WorldView);
	Font = GraphicFont(23651, 223);
}

void RenderSystem::SetBaseLight(sf::Color Color)
{
	RenderSprite.setColor(Color);
}

void RenderSystem::SetLayerVisible(int Layer, bool Visible)
{
	DrawLayer[Layer] = Visible;
}
