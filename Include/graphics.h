#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <vector>
#include <SFML/Graphics.hpp>

struct GraphicData
{
	uint32_t FileID;

	uint16_t StartX;
	uint16_t StartY;
	uint16_t PixelWidth;
	uint16_t PixelHeight;
	float TileWidth;
	float TileHeight;
		
	uint32_t Frames[32];
	uint16_t FrameCount;
	float Speed;
};

struct GraphicResources
{
	std::vector<GraphicData> Graphics;
	std::vector<std::vector<std::vector<int>>> Animations;
	std::map<int, sf::Texture> Textures;

	GraphicData& GetGraphic(int Index);
	int GetGraphicCount();
	int GetAnimation(int BodyPart, int AnimIndex, int Heading);
	sf::Sprite GenerateSpriteFromGrhIndex(int GrhIndex, bool Centered);
	void LoadAll();
	void LoadGraphicData();
	void LoadTextures();
	void LoadAnimations();
};

#endif
