#include "tile.hpp"

#include <unordered_map>

static const std::unordered_map<tile::type, std::string> TYPE_STRS{
	{ tile::Air, "Air" },
	{ tile::Block, "Block" },
	{ tile::Spike, "Spike" },
	{ tile::Start, "Start" },
	{ tile::End, "End" }
};

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
	: m_type(Air),
	  m_attrs(TYPE_DEFAULT_ATTRS.at(Air)),
	  m_dir(Up) {
}

tile::tile(tile::type t)
	: m_type(t),
	  m_attrs(TYPE_DEFAULT_ATTRS.at(t)),
	  m_dir(Up) {
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

std::string tile::type_to_str(tile::type t) {
	return TYPE_STRS.at(t);
}

tile::type tile::str_to_type(const std::string& s) {
	auto found = std::find_if(TYPE_STRS.begin(), TYPE_STRS.end(), [&s](auto&& p) {
		return p.second == s;
	});
	if (found == TYPE_STRS.end()) {
		return Air;
	} else {
		return found->first;
	}
}

nlohmann::json tile::serialize() const {
	return {
		{ "type", type_to_str(m_type) }
	};
}

void tile::deserialize(const nlohmann::json& j) {
	m_type = str_to_type(j.at("type").get<std::string>());
}
