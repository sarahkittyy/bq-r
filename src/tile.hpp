#pragma once

#include <json.hpp>

/**
 * @brief one of the many tiles in a level
 */
class tile {
public:
	/**
	 * @brief the type of this tile
	 *
	 * @remarks please don't ever change these numbers
	 */
	enum type {
		Air	  = 0,
		Block = 1,
		Spike = 2,
		Start = 3,
		End	  = 4,
	};

	/**
	 * @brief tile attributes
	 */
	enum attrs {
		Nil		= 0 << 0,
		Solid	= 1 << 0,
		Harmful = 1 << 1,
	};

	/**
	 * @brief the direction this tile is facing
	 */
	enum dir {
		Left  = 0,
		Right = 1,
		Up	  = 2,
		Down  = 3,
	};

	/**
	 * @brief construct to a specific tile type
	 *
	 * @param t 
	 */
	tile(type t = type::Air, dir d = dir::Up);

	/**
	 * @brief get this tile's type
	 *
	 */
	type get_type() const;

	/**
	 * @brief set this tile's type
	 *
	 * @param t
	 * @param refresh Update the attributes to the new type's default
	 */
	void set_type(type t, bool refresh = true);

	/**
	 * @brief retrieve the tile's direction
	 *
	 */
	dir get_dir() const;

	/**
	 * @brief update the tile's direction
	 *
	 * @param d the new direction
	 */
	void set_dir(dir d);

	/**
	 * @brief serialize this tile into a simple json object
	 *
	 */
	nlohmann::json serialize() const;

	/**
	 * @brief overwrite this tile with the data found in the json obect
	 *
	 * @param j valid tile json generated from serialize()
	 */
	void deserialize(const nlohmann::json& j);

private:
	// the tile type
	type m_type;

	// tile attributes
	int m_attrs;

	// tile direction
	dir m_dir;
};
