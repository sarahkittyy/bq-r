#include "level.hpp"

#include <algorithm>
#include <cassert>

level::level(int width, int height)
	: m_width(width), m_height(height) {
	m_tiles = new tile[m_width * m_height];
}

level::level(const level& other)
	: m_width(other.m_width), m_height(other.m_height) {
	m_tiles = new tile[m_width * m_height];
	memcpy(m_tiles, other.m_tiles, sizeof(tile) * m_width * m_height);
}

level::level(const nlohmann::json& data) {
	// for deserialize to not break :D
	m_tiles = new tile[1];
	deserialize(data);
}

level::~level() {
	delete[] m_tiles;
}

void level::set_tile(int x, int y, tile t) {
	m_tiles[c2i(x, y)] = t;
}

tile& level::get_tile(int x, int y) {
	return m_tiles[c2i(x, y)];
}

const tile& level::get_tile(int x, int y) const {
	return m_tiles[c2i(x, y)];
}

nlohmann::json level::serialize() const {
	using nlohmann::json;

	// convert all tiles to json
	std::vector<tile> tiles_v(m_tiles, m_tiles + m_width * m_height);
	std::vector<json> tiles_j;
	tiles_j.resize(tiles_v.size());
	std::transform(tiles_v.begin(), tiles_v.end(), tiles_j.begin(),
				   [](const tile& t) -> json {
					   return t.serialize();
				   });

	json j = {
		{ "width", m_width },
		{ "height", m_height },
	};
	j["tiles"] = tiles_j;

	return j;
}

void level::deserialize(const nlohmann::json& j) {
	using nlohmann::json;

	delete[] m_tiles;
	m_width	 = j.at("width").get<int>();
	m_height = j.at("height").get<int>();
	m_tiles	 = new tile[m_width * m_height];

	int idx = 0;
	for (auto& t : j.at("tiles").get<std::vector<json>>()) {
		assert(t.is_object());
		m_tiles[idx].deserialize(t);
		idx++;
	}
}

int level::c2i(int x, int y) const {
	assert(x >= 0 && x < m_width);
	assert(y >= 0 && y < m_height);
	return x + y * m_width;
}
