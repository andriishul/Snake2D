#include "Image.hpp"
#include <utility>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "string"
#include <stdexcept>
Image::~Image()
{
	STBI_FREE(m_Pixels);
}

Image::Image(const Image& image) : m_Pixels(std::move(const_cast<Image&>(image).m_Pixels)),
	m_Height(image.m_Height), m_Width(image.m_Width), m_NrChannels(image.m_NrChannels)
{
	
}

Image::Image(const char* file)
{
	std::string filePath = ASSETS_IMAGES_DIR;
	filePath += file;
	m_Pixels = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_NrChannels, STBI_default);
	const char* error = stbi_failure_reason();
	if (error)
		throw std::runtime_error("Error::Image" + std::string(error));
}
