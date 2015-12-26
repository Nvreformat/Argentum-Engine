#include "dialog.h"
#include "engine.h"
#include "Lib/stringutils.h"

void Dialog::Draw()
{
	if (Visible)
	{
		ElapsedTime += Engine.Renderer.ElapsedTime;
		if (ElapsedTime > 5000)
		{
			Hide();
			ElapsedTime = 0;

			return;
		}

		if (Elevation < MaxElevation)
		{
			Elevation += ElevationSpeed;
			Update();
		}

		GraphicText::Draw();
	}
}

std::vector<std::string> Dialog::FormatString(std::string Text)
{
	std::vector<std::string> Ret;

	int I = 0;

	if (Text.size() > 0)
	{
		while(true)
		{
			int TextSize = Text.size();

			if (TextSize >= ((I + 1) * DialogSize))
			{
				Ret.push_back(Text.substr(I * DialogSize, DialogSize));
			}
			else
			{
				Ret.push_back(Text.substr(I * DialogSize, TextSize - (I * DialogSize)));

				break;
			}

			I++;
		}
	}

	std::reverse(Ret.begin(), Ret.end());

	return Ret;
}

void Dialog::Update()
{
	int TextWidth = GetTextWidth(Text);
	int TextLength = Text.size();
	if (TextLength > DialogSize)
		TextWidth = GetTextWidth(Text.substr(0, DialogSize));

	int XOffset = 0;

	if (Alignment == 1)
		XOffset -= (TextWidth / 2);
	else if (Alignment == 2)
		XOffset -= TextWidth;

	std::vector<std::string> Lines = FormatString(Text);
	Characters.clear();

	for (std::size_t Line = 0; Line < Lines.size(); Line++)
	{
		int XOffsetTemp = XOffset;

		int StringLenght = Lines[Line].size();
		const char* CString = Lines[Line].c_str();

		for (int I = 0; I < StringLenght; I++)
		{
			Characters.resize(Characters.size() + 1);
			int Index = Characters.size() - 1;

			Characters[Index] = Engine.Renderer.Font.GetCharacter(CString[I]);
			sf::FloatRect Bounds = Characters[Index].getGlobalBounds();

			Characters[Index].setPosition(Position.x + XOffsetTemp, Position.y - Bounds.height - (Line * Bounds.height) - ((int)Elevation) + MaxElevation);
			Characters[Index].setColor(Color);

			XOffsetTemp += Bounds.width;
		}
	}
}

void Dialog::Show()
{
	Visible = true;

	Elevation = 0;
	ElapsedTime = 0;
}

void Dialog::Hide()
{
	Visible = false;
}
