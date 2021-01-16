#include "level.hpp"

#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>
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

std::vector<level::body> level::optimize_bodies() const {
	std::vector<level::body> bodies;   //basic setup of variables
	int cur_level		= 0;
	int prev_level		= 0;
	tile::type cur_type = m_tiles[0].get_type();
	int cur_start		= 0;
	int cur_end			= 0;
	int arrSize			= m_width * m_height;
	for (int i = 1; i < arrSize; i++) {	  //initial loop through all the tiles joining tiles of the same type along the same height.
		cur_level = i / m_width;
		if (cur_level == prev_level && cur_type == m_tiles[i].get_type() and cur_type != 0) {
			cur_end = i % m_width;
		} else if (cur_type != 0) {
			sf::IntRect r;
			r.left			 = cur_start;
			r.top			 = prev_level;
			r.width			 = cur_end - cur_start + 1;
			r.height		 = 1;
			level::body temp = { prev_level, cur_type, r };
			bodies.push_back(temp);

			cur_start  = i % m_width;
			cur_end	   = i % m_width;
			prev_level = cur_level;
			cur_type   = m_tiles[i].get_type();
		} else {
			cur_start  = i % m_width;
			cur_end	   = i % m_width;
			prev_level = cur_level;
			cur_type   = m_tiles[i].get_type();
		}
	}
	int did_stuff = 1;

	while (did_stuff) {	  //loop through the recently generated bodies vector and join all bodies that have the same start and end, that are also able to be joined into 1 body. not optimal but wokrs for now.
		did_stuff = 0;
		for (int i = 0; i < (int)bodies.size(); i++) {
			for (int j = i + 1; j < (int)bodies.size(); j++) {
				if (bodies[i].bounds.left == bodies[j].bounds.left && bodies[i].bounds.width == bodies[j].bounds.width && bodies[i].type == bodies[j].type) {
					if (bodies[i].bounds.top + bodies[i].bounds.height == bodies[j].bounds.top || bodies[i].bounds.top == bodies[j].bounds.top + bodies[j].bounds.height) {
						sf::IntRect r;
						r.left			   = bodies[i].bounds.left;
						r.top			   = std::min(bodies[j].bounds.top, bodies[i].bounds.top);
						r.width			   = bodies[i].bounds.width;
						r.height		   = bodies[j].bounds.height + bodies[i].bounds.height;
						level::body temper = { r.top, bodies[j].type, r };
						if (j == (int)bodies.size() - 1) {
							bodies.pop_back();
						} else {
							bodies[j] = bodies.back();
							bodies.pop_back();
						}
						if (i == (int)bodies.size() - 1) {
							bodies.pop_back();
						} else {
							bodies[i] = bodies.back();
							bodies.pop_back();
						}

						bodies.push_back(temper);
						did_stuff = 1;
						break;
					}
				}
			}
			if (did_stuff) break;
		}
	}

	return bodies;
}

int level::c2i(int x, int y) const {
	assert(x >= 0 && x < m_width);
	assert(y >= 0 && y < m_height);
	return x + y * m_width;
}
