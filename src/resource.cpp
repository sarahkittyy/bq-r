#include "resource.hpp"

#include <fstream>
#include <stdexcept>

sf::Texture& resource::texture(const std::string& path) {
	if (!m_tex.contains(path)) {
		m_tex[path].loadFromFile(path);
	}
	return m_tex[path];
}

const nlohmann::json& resource::json(const std::string& path) {
	if (!m_json.contains(path)) {
		std::ifstream f(path);
		if (!f) {
			throw std::runtime_error("Could not load json file at path " + path + ".");
		}
		f >> m_json[path];
	}
	return m_json[path];
}
