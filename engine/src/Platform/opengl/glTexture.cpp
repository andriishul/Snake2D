#include "glTexture.hpp"
#include "glad/glad.h"
#include "Image.hpp"
#include <stdexcept>

glTexture2D::glTexture2D(): m_ID(0)
{
}
glTexture2D::glTexture2D(const std::string& filename)
{
	Image image = (ASSETS_IMAGES_DIR + filename).c_str();

	switch (image.GetChannels())
	{
	case 1:
		m_Format = GL_RED;
		break;
	case 2:
		m_Format = GL_RG;
		break;
	case 3:
		m_Format = GL_RGB;
		break;
	case 4:
		m_Format = GL_RGBA;
		break;
	}
	glGenTextures(1,&m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, m_Format, image.GetWidth(), image.GetHeight(), 0, m_Format, GL_UNSIGNED_BYTE, image.GetPixels());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glBindTexture(GL_TEXTURE_2D, 0);
}
glTexture2D::~glTexture2D() 
{
	if (glIsTexture(m_ID))
		glDeleteTextures(1, &m_ID);
}

glTexture2D::glTexture2D(int width, int height, PixelFormat format):
	m_Height(height), m_Width(width)
{
	GLenum internalFormat = GL_R8;
	m_Format = GL_RGB;
	switch (format)
	{
	case PixelFormat::RED:
		internalFormat = GL_R8;
		m_Format = GL_RED;
		break;
	case PixelFormat::RG:
		internalFormat = GL_RG8;
		m_Format = GL_RG;
		break;
	case PixelFormat::RGB:
		internalFormat = GL_RGB8;
		m_Format = GL_RGB;
		break;
	case PixelFormat::RGBA:
		internalFormat = GL_RGBA16;
		m_Format = GL_RGBA;
		break;
	default:
		throw std::runtime_error("Image format not found");
	}
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat , width, height);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void glTexture2D::SetData(const void* pixels)
{
	SetData(0, 0, m_Width, m_Height, pixels);
}
void glTexture2D::SetData(int xOff, int yOff, int width, int height, const void* pixels)
{
	glTextureSubImage2D(m_ID, 0, xOff, yOff, width, height, m_Format, GL_UNSIGNED_BYTE, pixels);
}
void glTexture2D::Bind(int unit) const
{
	glBindTextureUnit(unit, m_ID);
}
