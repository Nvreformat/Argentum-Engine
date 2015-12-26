#include <string>
#include <vector>
#include <stdio.h>
#include "graphics.h"
#include "engine.h"
#include "Lib/BufferedFile.h"
#include "Lib/getvar.h"

using namespace std;
using namespace sf;

int GraphicResources::GetGraphicCount()
{
	return Graphics.size() - 1;
}

GraphicData& GraphicResources::GetGraphic(int Index)
{
	return Graphics[Index];
}

void GraphicResources::LoadAll()
{
	LoadGraphicData();
	LoadTextures();
	LoadAnimations();
}

void GraphicResources::LoadTextures()
{
	int GraphicCount = GetGraphicCount();

	for (int I = 1; I <= GraphicCount; I++)
	{
		GraphicData& Graphic = GetGraphic(I);

		if (Textures.count(Graphic.FileID) == 0)
		{
			Textures[Graphic.FileID] = Texture();

			Textures[Graphic.FileID].loadFromFile("Resources/Graphics/" + to_string(Graphic.FileID) + ".png");
		}
	}
}

int GraphicResources::GetAnimation(int BodyPart, int AnimIndex, int Heading)
{
	return Animations[BodyPart][AnimIndex][Heading];
}

void GraphicResources::LoadGraphicData()
{
	BufferedFile File = BufferedFile("Resources/Graficos.ind", "rb");
	
	int FileVersion = File.Read(&FileVersion);
	unsigned int GraphicCount = File.Read(&GraphicCount);
	
	printf("GrhCount %u\n", GraphicCount);
	
	Graphics.resize(GraphicCount + 1);

	while(true)
	{
		GraphicData Graphic;
	
		unsigned int Index = File.Read(&Index);
	
		if (Index != 0)
		{
			Graphic.FrameCount = File.Read(&Graphic.FrameCount);
			
			if (Graphic.FrameCount > 1)
			{
				for (int I = 0; I < Graphic.FrameCount; I++)
				{
					Graphic.Frames[I] = File.Read(&Graphic.Frames[I]);
					
					if (Graphic.Frames[I] <= 0 || Graphic.Frames[I] > GraphicCount)
						return;
				}
				
				Graphic.Speed = File.Read(&Graphic.Speed);
				if (Graphic.Speed <= 0)
					return;
					
				Graphic.StartX = Graphics[Graphic.Frames[0]].StartX;
				if (Graphic.StartX < 0)
					return;
					
				Graphic.StartY = Graphics[Graphic.Frames[0]].StartY;
				if (Graphic.StartY < 0)
					return;

				Graphic.TileWidth = Graphics[Graphic.Frames[0]].TileWidth;
				Graphic.TileHeight = Graphics[Graphic.Frames[0]].TileHeight;
			}
			else
			{
				Graphic.FileID = File.Read(&Graphic.FileID);
				if (Graphic.FileID <= 0)
					return;
					
				Graphic.StartX = File.Read(&Graphic.StartX);
				if (Graphic.StartX < 0)
					return;
					
				Graphic.StartY = File.Read(&Graphic.StartY);
				if (Graphic.StartY < 0)
					return;
					
				Graphic.PixelWidth = File.Read(&Graphic.PixelWidth);
				if (Graphic.PixelWidth <= 0)
					return;
					
				Graphic.PixelHeight = File.Read(&Graphic.PixelHeight);
				if (Graphic.PixelHeight <= 0)
					return;
					
				Graphic.TileWidth = Graphic.PixelWidth / 32;
				Graphic.TileHeight = Graphic.PixelHeight / 32;
				
				Graphic.Frames[0] = Index; 
			}
			
			Graphics[Index] = Graphic;
		}
		
		if (Index == GraphicCount)
			break;
	}
}

void GraphicResources::LoadAnimations()
{
	printf("Loading animations\n");
	Animations.resize(5);

	int Count = GetVarInt("Resources/Cabezas.ini", "INIT", "NumHeads");
	printf("Head count: %u\n", Count);

	for (int I = 0; I < Count; ++I)
	{
		vector<int> Anim;

		Anim.push_back(GetVarInt("Resources/Cabezas.ini", "HEAD" + to_string(I), "Head1"));
		Anim.push_back(GetVarInt("Resources/Cabezas.ini", "HEAD" + to_string(I), "Head2"));
		Anim.push_back(GetVarInt("Resources/Cabezas.ini", "HEAD" + to_string(I), "Head3"));
		Anim.push_back(GetVarInt("Resources/Cabezas.ini", "HEAD" + to_string(I), "Head4"));

		Animations[0].push_back(Anim);
	}

	Count = GetVarInt("Resources/Cuerpos.ini", "INIT", "NumBodies");
	printf("Torso count: %u\n", Count);

	for (int I = 0; I < Count; ++I)
	{
		vector<int> Anim;

		Anim.push_back(GetVarInt("Resources/Cuerpos.ini", "BODY" + to_string(I), "WALK1"));
		Anim.push_back(GetVarInt("Resources/Cuerpos.ini", "BODY" + to_string(I), "WALK2"));
		Anim.push_back(GetVarInt("Resources/Cuerpos.ini", "BODY" + to_string(I), "WALK3"));
		Anim.push_back(GetVarInt("Resources/Cuerpos.ini", "BODY" + to_string(I), "WALK4"));

		Animations[1].push_back(Anim);
	}

	Count = GetVarInt("Resources/Cascos.ini", "INIT", "NumCascos");
	printf("Helmet count: %u\n", Count);

	for (int I = 0; I < Count; ++I)
	{
		vector<int> Anim;

		Anim.push_back(GetVarInt("Resources/Cascos.ini", "CASCO" + to_string(I), "Head1"));
		Anim.push_back(GetVarInt("Resources/Cascos.ini", "CASCO" + to_string(I), "Head2"));
		Anim.push_back(GetVarInt("Resources/Cascos.ini", "CASCO" + to_string(I), "Head3"));
		Anim.push_back(GetVarInt("Resources/Cascos.ini", "CASCO" + to_string(I), "Head4"));

	Animations[2].push_back(Anim);
	}

	Count = GetVarInt("Resources/Armas.ini", "INIT", "NumArmas");
	printf("Weapon count: %u\n", Count);

	for (int I = 0; I < Count; ++I)
	{
		vector<int> Anim;

		Anim.push_back(GetVarInt("Resources/Armas.ini", "Arma" + to_string(I), "Dir1"));
		Anim.push_back(GetVarInt("Resources/Armas.ini", "Arma" + to_string(I), "Dir2"));
		Anim.push_back(GetVarInt("Resources/Armas.ini", "Arma" + to_string(I), "Dir3"));
		Anim.push_back(GetVarInt("Resources/Armas.ini", "Arma" + to_string(I), "Dir4"));

		Animations[3].push_back(Anim);
	}

	Count = GetVarInt("Resources/Escudos.ini", "INIT", "NumEscudos");
	printf("Shield count: %u\n", Count);

	for (int I = 0; I < Count; ++I)
	{
		vector<int> Anim;

		Anim.push_back(GetVarInt("Resources/Escudos.ini", "ESC" + to_string(I), "Dir1"));
		Anim.push_back(GetVarInt("Resources/Escudos.ini", "ESC" + to_string(I), "Dir2"));
		Anim.push_back(GetVarInt("Resources/Escudos.ini", "ESC" + to_string(I), "Dir3"));
		Anim.push_back(GetVarInt("Resources/Escudos.ini", "ESC" + to_string(I), "Dir4"));

		Animations[4].push_back(Anim);
	}
}

Sprite GraphicResources::GenerateSpriteFromGrhIndex(int GrhIndex, bool Centered)
{
	Sprite Sprite;
	GraphicData& Frame = GetGraphic(GetGraphic(GrhIndex).Frames[0]);

	Sprite.setTexture(Textures[Frame.FileID]);
	Sprite.setTextureRect(IntRect(Frame.StartX, Frame.StartY, Frame.PixelWidth, Frame.PixelHeight));

	if (Centered)
	{
		int OriginX = (int)(((int)Frame.TileWidth) * 16) + 16;
		int OriginY = (int)((((int)Frame.TileHeight) * 32) + 32);

		Sprite.setOrigin(OriginX, OriginY);
	}

	return Sprite;
}
