#pragma once

class Image 
{
public:
	~Image();
	Image() = delete;
	Image(const Image& image);
	// Loads a image from the specified filename in the 'assets/images' directory
	Image(const char* file);

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	int GetChannels() const { return m_NrChannels; }
	unsigned char* GetPixels() const { return m_Pixels; }
private:
	int m_Width, m_Height;
	int m_NrChannels;
	unsigned char* m_Pixels;
};