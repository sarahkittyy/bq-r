#include "resource_mgr.hpp"

sf::Texture& resource::texture(const std::string& path) {
	if (!m_tex.contains(path)) {
		m_tex[path].loadFromFile(path);
	}
	return m_tex[path];
}
