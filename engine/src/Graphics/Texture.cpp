#include "Texture.hpp"
#include "platform/opengl/glTexture.hpp"

Texture2D* Texture2D::Create(int width, int height, PixelFormat format)
{
	return new glTexture2D(width, height, format);
}
