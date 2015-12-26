#ifndef DIALOG_H
#define DIALOG_H

#include "graphicfont.h"

class Dialog : public GraphicText
{
	using GraphicText::GraphicText;

protected:
	static const int DialogSize = 25;
	static const int MaxElevation = 15;
	static constexpr double ElevationSpeed = 1.5;

	double ElapsedTime = 0;
	double Elevation = 0;
	bool Visible = false;

	void Update() override;
	std::vector<std::string> FormatString(std::string Text);

public:
	void Draw();
	void Show();
	void Hide();
};

#endif
