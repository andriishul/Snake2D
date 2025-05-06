#pragma once
#include <Graphics/Font.hpp>
#include <Graphics/Shader.hpp>

#include <memory>
#include <vector>

class ResourceLoader 
{
public:
	// Loads a 2D texture from the specified filename in the 'assets/images' directory, caching it if it's not already loaded.
	// Returns a pointer to the loaded texture.
	static const Texture2D* LoadTexture2D(const std::string& filename);

	// Loads a font from the specified filename in the 'assets/fonts' directory, caching it if it's not already loaded.
	// Returns a pointer to the loaded font.
	static const Font* LoadFont(const std::string& filename);

	// Loads a .vert/.frag shader by name from the 'assets/shaders' directory, caching it if it's not already loaded.
	// @param name Shader name (without extension).
	// @return Pointer to the cached shader.
	static Shader* LoadShader(const std::string& name);
private:
	static std::map<std::string, std::unique_ptr<Texture2D>> s_LoadedTextures2D;
	static std::map<std::string, std::unique_ptr<Font>> s_LoadedFonts;
	static std::map<std::string, std::unique_ptr<Shader>> s_LoadedShaders;
};