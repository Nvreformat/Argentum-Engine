#include <SFML/Graphics.hpp>
#include "graphics.h"
#include "engine.h"
#include "drawableentity.h"

using namespace sf;

DrawableEntity::DrawableEntity(int GraphicIndex, bool Centered, bool Animated)
{
	if (GraphicIndex > 0)
	{
		this->GrhIndex = GraphicIndex;
		this->Animated = Animated;

		GraphicData& Original = Engine.Graphics.GetGraphic(GraphicIndex);

		FrameCount = Original.FrameCount;
		Speed = Original.Speed;

		Frames.resize(FrameCount);

		for (int I = 0; I < FrameCount; I++)
		{
			Frames[I] = Engine.Graphics.GenerateSpriteFromGrhIndex(Original.Frames[I], Centered);
		}

		SetPosition(0, 0);
	}
}

void DrawableEntity::SetPosition(int X, int Y)
{
	for (int I = 0; I < FrameCount; I++)
	{
		Frames[I].setPosition(X, Y);
	}
}

void DrawableEntity::SetOrigin(int X, int Y)
{
	for (int I = 0; I < FrameCount; I++)
	{
		Frames[I].setOrigin(32 - X, 64 - Y);
	}
}

const IntRect& DrawableEntity::GetSize()
{
	return Frames[0].getTextureRect();
}

void DrawableEntity::Draw()
{
	if (FrameCount > 0)
	{
		RenderSystem& Renderer = Engine.Renderer;

		if (Animated && FrameCount > 1)
		{
			FrameCounter += (Renderer.ElapsedTime * FrameCount / Speed);
			CurrentFrame = ((int)FrameCounter) % FrameCount;
		}

		Renderer.Buffer.draw(Frames[CurrentFrame]);
	}
}
