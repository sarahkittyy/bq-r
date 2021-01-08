#include "tile.hpp"

static const std::vector<std::string> TYPE_STRS{
	"AIR",
	"BLOCK",
	"SPIKE",
	"START",
	"END"
};

tile::tile()
	: m_type(AIR) {
}

tile::tile(tile::type t)
	: m_type(t) {
}

tile::type tile::get_type() const {
	return m_type;
}

void tile::set_type(tile::type t) {
	m_type = t;
}

std::string tile::type_to_str(tile::type t) {
	return TYPE_STRS.at((int)t);
}

tile::type tile::str_to_type(const std::string& s) {
	for (int i = 0; i < TYPE_STRS.size(); ++i) {
		if (TYPE_STRS[i] == s) {
			return (tile::type)i;
		}
	}
	return AIR;
}

nlohmann::json tile::serialize() const {
	return {
		{ "type", type_to_str(m_type) }
	};
}

void tile::deserialize(const nlohmann::json& j) {
	m_type = str_to_type(j.at("type").get<std::string>());
}
