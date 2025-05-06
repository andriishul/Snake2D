#pragma once
#include <Graphics/Texture.hpp>
#include "Transformable2D.hpp"

// When no texture is applied, the sprite is rendered as a colored quad (rectangle).
class Sprite : public Transformable2D
{
public:
	Sprite(glm::vec2 position = { 0.f,0.f }, glm::vec2 scale = { 1.f,1.f },
		glm::vec3 color = { 1.f,1.f,1.f }, float rotation = 0.f, const Texture2D* texture = nullptr);

	void SetTexture(const Texture2D* texture) { m_Texture = texture; }
	const Texture2D* GetTexture() const { return m_Texture; }
private:
	const Texture2D* m_Texture;
};