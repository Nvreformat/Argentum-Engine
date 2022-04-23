#ifndef DRAWABLE_ENTITY_H
#define DRAWABLE_ENTITY_H

#include "SFML/Graphics.hpp"
#include "graphics.h"

struct DrawableEntity
{
	int GrhIndex = 0;
	int FrameCount = 0;
	int CurrentFrame = 0;
	double Speed = 0;
	double FrameCounter = 0;
	bool Animated = false;
	std::vector<sf::Sprite> Frames = std::vector<sf::Sprite>();

	void SetPosition(int X, int Y);
	void SetOrigin(int X, int Y);
	const sf::IntRect& GetSize();
	DrawableEntity(int GraphicIndex, bool Centered, bool Animated);
	DrawableEntity() : DrawableEntity(0, false, false) {}
	void Draw();
};

#endif
