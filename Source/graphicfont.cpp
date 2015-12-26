#include "graphicfont.h"
#include "engine.h"
#include <iostream>

GraphicFont::GraphicFont(int GraphicIndexStart, int CharacterCount)
{
	Characters.resize(CharacterCount);

	for (int I = GraphicIndexStart; I < (GraphicIndexStart + CharacterCount); I++)
	{
		Characters[I - GraphicIndexStart] = Engine.Graphics.GenerateSpriteFromGrhIndex(I, false);
	}
}

sf::Sprite& GraphicFont::GetCharacter(char Character)
{
	return Characters[Character - 32];
}

void GraphicText::Update()
{
	int TextLenght = GetTextWidth(Text);
	int XOffset = 0;

	if (Alignment == 1)
		XOffset -= (TextLenght / 2);
	else if (Alignment == 2)
		XOffset -= TextLenght;

	int StringLenght = Text.size();
	const char* CString = Text.c_str();

	Characters.resize(StringLenght);

	for (int I = 0; I < StringLenght; I++)
	{
		Characters[I] = Engine.Renderer.Font.GetCharacter(CString[I]);
		sf::FloatRect Bounds = Characters[I].getGlobalBounds();

		Characters[I].setPosition(Position.x + XOffset, Position.y - Bounds.height);
		Characters[I].setColor(Color);

		XOffset += Bounds.width;
	}
}

GraphicText::GraphicText(std::string Text, sf::Vector2f Position, sf::Color Color, int Alignment)
{
	this->Text = Text;
	this->Position = Position;
	this->Color = Color;
	this->Alignment = Alignment;

	Update();
}

int GraphicText::GetTextWidth(std::string Text)
{
	int Lenght = 0;
	int StringLenght = Text.size();
	const char* CString = Text.c_str();

	for (int I = 0; I < StringLenght; I++)
	{
		sf::Sprite Character = Engine.Renderer.Font.GetCharacter(CString[I]);

		Lenght += Character.getGlobalBounds().width;
	}

	return Lenght;
}

void GraphicText::Draw()
{
	int Size = Characters.size();

	for (int I = 0; I < Size; I++)
	{
		Engine.Renderer.Buffer.draw(Characters[I]);
	}
}

void GraphicText::SetText(std::string Text)
{
	this->Text = Text;

	Update();
}

std::string GraphicText::GetText()
{
	return Text;
}

void GraphicText::SetColor(sf::Color Color)
{
	this->Color = Color;

	for (std::size_t I = 0; I < Characters.size(); I++)
	{
		Characters[I].setColor(Color);
	}
}

sf::Color GraphicText::GetColor()
{
	return Color;
}

void GraphicText::SetPosition(sf::Vector2f Position)
{
	SetPosition(sf::Vector2f(Position.x, Position.y));
}

void GraphicText::SetPosition(float X, float Y)
{
	Position.x = X;
	Position.y = Y;

	Update();
}

sf::Vector2f GraphicText::GetPosition()
{
	return Position;
}
