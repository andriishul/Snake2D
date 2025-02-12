#pragma once
#include "OrthoCamera.hpp"
#include <Entity/Sprite.hpp>
#include "Entity/Text.hpp"

class Renderer2D 
{
public:
	static void Init();

	static void Begin(OrthoCamera& camera);
	
	static void DrawText(const Text&);
	static void DrawSprite(const Sprite&);
	
	static void End();
};