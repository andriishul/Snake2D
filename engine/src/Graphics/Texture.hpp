 #pragma once

enum class PixelFormat
{
	RED,
	RG,
	RGB,
	RGBA
};

class Texture2D
{
public:
	virtual ~Texture2D() = default;

	virtual void Bind(int unit = 0) const = 0;

	virtual void SetData(const void*) = 0;
	virtual void SetData(int xOff, int yOff, int width, int height, const void* pixels) = 0;

	virtual int GetHeight() const = 0;
	virtual int GetWidth() const = 0;

	static Texture2D* Create(int width, int height, PixelFormat format);
}; 
