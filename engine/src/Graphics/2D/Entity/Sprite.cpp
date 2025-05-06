#include "Sprite.hpp"
Sprite::Sprite(glm::vec2 position, glm::vec2 scale, glm::vec3 color, float rotation, const Texture2D* texture) : Transformable2D(position, scale, color, rotation)
{
	SetTexture(texture);
}



