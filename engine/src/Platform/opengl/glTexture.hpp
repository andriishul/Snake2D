#pragma once
#include <Graphics/Texture.hpp>
#include <string>

class glTexture2D : public Texture2D
{
public:
	virtual ~glTexture2D();
	/**
	 * @brief Creates an empty 2D texture.
	 *
	 * This function initializes a new 2D texture object without any image data. It is commonly used to create texture objects that will be populated later with image data or used as placeholder textures.
	 */	
	glTexture2D();
	// Loads a 2D texture from an image file in 'assets/images'.
	// Parameters:
	// filename: Image file name.	
	glTexture2D(const std::string& filename);
	// Creates a texture from specified data.
	glTexture2D(int width, int height, PixelFormat format);

	virtual void Bind(int unit) const override;

	virtual void SetData(const void*) override;
	virtual void SetData(int xOff, int yOff, int width, int height, const void* pixels) override;

	virtual int GetHeight() const override { return m_Height; }
	virtual int GetWidth() const override { return m_Width; }
private:
	unsigned m_ID, m_Format;
	int m_Height, m_Width;
};