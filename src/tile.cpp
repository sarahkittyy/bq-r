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

tile::tile()
	: m_type(0),
	  m_attrs(TYPE_DEFAULT_ATTRS.at(type::Air)),
	  m_dir(0) {
}

tile::tile(tile::type t)
	: m_type(t),
	  m_attrs(TYPE_DEFAULT_ATTRS.at(t)),
	  m_dir(d) {
}

tile::type tile::get_type() const {
	return m_type;
}

void tile::set_type(tile::type t, bool refresh) {
	m_type = t;
	if (refresh) {
		m_attrs = TYPE_DEFAULT_ATTRS.at(t);
	}
}

tile::dir tile::get_dir() const {
	return m_dir;
}

void tile::set_dir(tile::dir d) {
	m_dir = d;
}

nlohmann::json tile::serialize() const {
	json j= {
		{"type",m_type},
		{"atrrs",m_attrs},
		{"dir",m_dir}
	}
	return j;
}

void tile::deserialize(const nlohmann::json& j) {
	m_type = j.at("type").get<std:int>();
	m_attrs= j.at("atrrs").get<std:int>();
	m_dir = j.at("dir").get<std:int>();
}
