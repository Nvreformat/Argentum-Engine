#ifndef RENDER_H
#define RENDER_H

#include <graphicfont.h>
#include <SFML/Graphics.hpp>
#include <string>
#include "engine.h"
#include "misc.h"

struct RenderSystem
{
	sf::RenderWindow* Window;
	Dimension Position;
	Dimension Size;
	double ElapsedTime;
	double TicksPerFrame;
	GraphicFont Font;
	bool DrawLayer[4] = {true, true, true, true};
	sf::RenderTexture Buffer;
	sf::Sprite RenderSprite;
	sf::View WorldView;
	sf::Clock Clock;

	void Initialize(sf::RenderWindow* Window);
	void SetPosition(int X, int Y);
	Dimension& GetPosition();
	bool IsInBounds(int X, int Y);
	void SetSize(int X, int Y);
	Dimension& GetSize();
	void SetCameraPosition(int X, int Y);
	const sf::Vector2f GetCameraPosition();

	void Render();
	void ShowNextFrame();
	void SetBaseLight(sf::Color Color);
	void SetLayerVisible(int Layer, bool Visible);
};

#endif
