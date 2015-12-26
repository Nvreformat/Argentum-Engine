#include "engine.h"
#include "graphics.h"
#include "map.h"
#include "character.h"
#include <string>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

ArgentumEngine Engine;

void ArgentumEngine::Initialize(RenderWindow* Window, int RenderSizeX, int RenderSizeY)
{
	Graphics.LoadAll();
	Renderer.Initialize(Window);
	Renderer.SetSize(RenderSizeX, RenderSizeY);
}

void ArgentumEngine::Update()
{
	Entities.DoUpdates();
}

void ArgentumEngine::Render()
{
	Renderer.ShowNextFrame();
}
