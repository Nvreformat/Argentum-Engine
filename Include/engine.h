#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <SFML/Graphics.hpp>
#include "graphics.h"
#include "map.h"
#include <drawableentity.h>
#include "render.h"
#include "entity.h"

class ArgentumEngine
{
public:
	MapSystem Map;
	RenderSystem Renderer;
	EntitySystem Entities;
	GraphicResources Graphics;

	void Initialize(sf::RenderWindow* Window, int RenderSizeX, int RenderSizeY);
	void Update();
	void Render();
};

extern ArgentumEngine Engine;

#endif
