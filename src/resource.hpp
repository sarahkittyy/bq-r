#pragma once

#include <SFML/Graphics.hpp>
#include <json.hpp>
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

	/**
	 * @brief retrieve a json file at the given path
	 *
	 * @param path the path to the .json file
	 */
	const nlohmann::json& json(const std::string& path);

private:
	// all textures stored
	std::unordered_map<std::string, sf::Texture> m_tex;
	// all json files loaded
	std::unordered_map<std::string, nlohmann::json> m_json;
};
