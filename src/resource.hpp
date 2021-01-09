#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

/**
 * @brief stores and loads resources, keying them by path so no one asset is loaded any more than once
 */
class resource {
public:
	/**
	 * @brief retrieve a texture at the given path
	 *
	 * @param path the path to the texture
	 */
	sf::Texture& texture(const std::string& path);

private:
	// all textures stored
	std::unordered_map<std::string, sf::Texture> m_tex;
};
