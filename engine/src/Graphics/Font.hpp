#pragma once
#include "Texture.hpp"

#include <map>
#include <string>
#include <glm/glm.hpp>

struct Character {
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
    glm::vec2 TexCoords[2]; // Texture coordinates in the font atlas (top-left and bottom-right corners)
};

constexpr int DEFAULT_FONT_PIXEL_SIZE = 128;

class Font  
{   
protected:
    // Constructs a new Font object using the specified font file from the 'assets/fonts' directory with the given pixel size.
    // Parameters:
    // fontFileName: The name of the font file to be loaded (located in 'assets/fonts').
    // pixelSize: The size of the font in pixels (default is DEFAULT_FONT_PIXEL_SIZE).    
    Font(const std::string& fontFileName, int pixelSize = DEFAULT_FONT_PIXEL_SIZE);
public:
    Font() = delete;
    virtual ~Font();

    const Character &operator[](unsigned char c) const { return m_Characters.at(c); }
    const Texture2D* GetGlyphAtlas() const { return m_GlyphAtlas; }
    std::string GetFamilyName() const { return m_FamilyName; }
    std::string GetStyleName() const { return m_StyleName; }
    const int GetPixelSize() const { return m_PixelSize; }
    friend class ResourceLoader;
private:
    Texture2D* m_GlyphAtlas;
    std::map<unsigned char, Character> m_Characters;
    std::string m_FamilyName, m_StyleName;
    int m_PixelSize;
};