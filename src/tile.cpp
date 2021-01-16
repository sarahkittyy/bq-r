#include "tile.hpp"

#include <unordered_map>

static const std::unordered_map<tile::type, int> TYPE_DEFAULT_ATTRS{
	{ tile::Air, tile::Nil },
	{ tile::Block, tile::Solid },
	{ tile::Spike, tile::Solid | tile::Harmful },
	{ tile::Start, tile::Nil },
	{ tile::End, tile::Nil }
};

inline tile::attrs operator|(tile::attrs a, tile::attrs b) {
	return static_cast<tile::attrs>(static_cast<int>(a) | static_cast<int>(b));
}

tile::tile(tile::type t, tile::dir d)
	: m_type(t),
	  m_attrs(TYPE_DEFAULT_ATTRS.at(t)),
	  m_dir(d) {
}

void tile::set_type(tile::type t, bool refresh) {
	m_type = t;
	if (refresh) {
		m_attrs = TYPE_DEFAULT_ATTRS.at(t);
	}
}

tile::type tile::get_type() const {
	return m_type;
}

void tile::set_dir(tile::dir d) {
	m_dir = d;
}

tile::dir tile::get_dir() const {
	return m_dir;
}

sf::Vector2i tile::tex_loc(int tw) const {
	/*
	   for now, we're just assuming that the tiles
	   are in the same order as in the tile::type enum
	   maybe a more robust method will be necessary in the future but i hope not
	*/
	int tid = static_cast<int>(m_type) - 1;
	return sf::Vector2i(tid % tw, tid / tw);
}

nlohmann::json tile::serialize() const {
	return {
		{ "type", m_type },
		{ "attrs", m_attrs },
		{ "dir", m_dir }
	};
}

void tile::deserialize(const nlohmann::json& j) {
	m_type	= j.at("type").get<tile::type>();
	m_attrs = j.at("attrs").get<int>();
	m_dir	= j.at("dir").get<tile::dir>();
}
