#ifndef FONT_H
#define FONT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

class GraphicFont
{
private:
	std::vector<sf::Sprite> Characters;

public:
	GraphicFont(int GrhIndexStart, int CharacterCount);
	GraphicFont() {}

	sf::Sprite& GetCharacter(char Character);
};

class GraphicText
{
protected:
	std::vector<sf::Sprite> Characters;
	std::string Text = "";
	sf::Color Color = sf::Color::White;
	sf::Vector2f Position = sf::Vector2f(0, 0);
	int Alignment = 0;

	virtual void Update();

public:
	explicit GraphicText(std::string Text, sf::Vector2f Position, sf::Color Color, int Alignment);
	GraphicText() {}

	void SetText(std::string Text);
	std::string GetText();
	void SetColor(sf::Color);
	sf::Color GetColor();
	void SetPosition(sf::Vector2f Position);
	void SetPosition(float X, float Y);
	sf::Vector2f GetPosition();
	int GetTextWidth(std::string Text);
	void Draw();
};

#endif
