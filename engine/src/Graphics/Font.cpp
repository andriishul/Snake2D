#include "Font.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdexcept>
#include <math.h>

constexpr int MAX_ATLAS_HEIGHT = 4096, MAX_ATLAS_WIDTH = 4096;

Font::~Font()
{
    delete m_GlyphAtlas;
}
Font::Font(const std::string& fontFileName, int pixelSize)
    : m_PixelSize(pixelSize), m_GlyphAtlas(Texture2D::Create(MAX_ATLAS_WIDTH, MAX_ATLAS_HEIGHT, PixelFormat::RED))
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
    }
    std::string filePath = ASSETS_FONTS_DIR;
    filePath += fontFileName;
    FT_Face face;
    if (FT_New_Face(ft, filePath.c_str(), 0, &face))
    {
        FT_Done_FreeType(ft);
        throw std::runtime_error("ERROR::FREETYPE: Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, 0, pixelSize);

    size_t x = 0, y = 0;
    m_FamilyName = face->family_name;
    m_StyleName = face->style_name;

    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            FT_Done_Face(face);
            FT_Done_FreeType(ft);
            throw std::runtime_error("ERROR::FREETYPE: Failed to load Glyph");
        }

        if (x + face->glyph->bitmap.width >= MAX_ATLAS_WIDTH)
        {
            x = 0;
            y += face->glyph->bitmap.rows;
        }

        if (y + face->glyph->bitmap.rows > MAX_ATLAS_HEIGHT)
        {
            FT_Done_Face(face);
            FT_Done_FreeType(ft);
            throw std::runtime_error("ERROR::FREETYPE: Texture atlas overflow");
        }

        m_GlyphAtlas->SetData(x, y, face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);

        Character character;
        character.Advance = face->glyph->advance.x;
        character.Bearing = { face->glyph->bitmap_left, face->glyph->bitmap_top };
        character.Size = { face->glyph->bitmap.width, face->glyph->bitmap.rows };

        character.TexCoords[0].x = static_cast<float>(x) / MAX_ATLAS_WIDTH;
        character.TexCoords[0].y = static_cast<float>(y + face->glyph->bitmap.rows) / MAX_ATLAS_HEIGHT;
        character.TexCoords[1].x = static_cast<float>(x + face->glyph->bitmap.width) / MAX_ATLAS_WIDTH;
        character.TexCoords[1].y = static_cast<float>(y) / MAX_ATLAS_HEIGHT;

        m_Characters.emplace(c, character);
        x += face->glyph->bitmap.width;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
