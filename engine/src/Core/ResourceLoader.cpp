#include "ResourceLoader.hpp"
//#ifdef 
#include "platform/opengl/glTexture.hpp"
#include "platform/opengl/glShader.h"
//#endif 

std::map<std::string, std::unique_ptr<Texture2D>> ResourceLoader::s_LoadedTextures2D; 
std::map<std::string, std::unique_ptr<Font>> ResourceLoader::s_LoadedFonts;
std::map<std::string, std::unique_ptr<Shader>> ResourceLoader::s_LoadedShaders;

const Texture2D* ResourceLoader::LoadTexture2D(const std::string& filename)
{
	if (s_LoadedTextures2D.find(filename) == s_LoadedTextures2D.end())
		s_LoadedTextures2D[filename] = std::unique_ptr<Texture2D>(new glTexture2D(filename));
	return s_LoadedTextures2D[filename].get();
}

const Font* ResourceLoader::LoadFont(const std::string& filename)
{
	if (s_LoadedFonts.find(filename) == s_LoadedFonts.end())
		s_LoadedFonts[filename] = std::unique_ptr<Font>(new Font(filename));
	return s_LoadedFonts[filename].get(); 
}

Shader* ResourceLoader::LoadShader(const std::string& name)
{
	if (s_LoadedShaders.find(name) == s_LoadedShaders.end())
		s_LoadedShaders[name] = std::unique_ptr<Shader>(new glShader(name + ".vert", name + ".frag"));
	return s_LoadedShaders[name].get();
}
