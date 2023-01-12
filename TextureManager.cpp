#include "TextureManager.hpp"

TextureManager* TextureManager::m_s_instance = nullptr;

TextureManager::TextureManager() {
	assert(m_s_instance == nullptr);
	m_s_instance = this;
}
sf::Texture& TextureManager::get_texture(const std::string& name) {
	auto& texture_map = m_s_instance->m_textures;
	const auto keyValuePair = texture_map.find(name);

	if (keyValuePair != texture_map.end())
	{
		return keyValuePair->second;
	}
	else {
		auto& texture = texture_map[name];
		if (!texture.loadFromFile(name))
		{
			throw std::runtime_error("FAILED TO LOAD TEXTURE");
		}
		return texture;
	}
}