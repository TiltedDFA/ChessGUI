#pragma once
#include <SFML/Graphics.hpp>
#ifdef SFML_STATIC
#define assert(x)
#else
#include <assert.h>
#endif

class TextureManager
{
public:
	TextureManager();
	TextureManager(const TextureManager& other) = delete;//deleting copy construct
	void operator=(const TextureManager& other) = delete;
	TextureManager(const TextureManager&& other) = delete;//deleting move construct
	void operator=(TextureManager&& other) = delete;
	static sf::Texture& get_texture(const std::string& texture_name);
private:
	static TextureManager* m_s_instance;
	std::map<std::string, sf::Texture> m_textures;
};
